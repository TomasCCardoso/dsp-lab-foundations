# Ring Buffer — Design Notes

## 1. Problem

A ring buffer is a fixed-size data structure used to store a continuous
stream of samples while reusing a pre-allocated memory region.

In streaming DSP applications, samples are continuously produced and
consumed. A conventional array would require samples to be shifted whenever
new data arrives, introducing unnecessary memory operations.

The Ring Buffer avoids this by maintaining a write position (`head`) and
using modular indexing to wrap around the storage array.

The implementation is designed for sample-by-sample DSP processing and is
used as the internal history buffer of the FIR filter implemented in this
repository.

---

## 2. Requirements

The Ring Buffer shall:

- Use externally provided storage memory.
- Avoid dynamic memory allocation.
- Support insertion of individual samples.
- Reuse storage when the buffer becomes full.
- Keep track of the next write position.
- Keep track of the number of valid samples currently stored.
- Allow retrieval of samples relative to the most recently inserted sample.
- Reject access to samples that have not yet been stored.
- Provide an explicit mechanism for reporting access errors.
- Support read-only access to the buffer through `const` correctness.
- Operate with a fixed storage capacity.

The implementation should also maintain predictable memory usage and
constant-time insertion and retrieval operations.

---

## 3. Data Model

The Ring Buffer maintains four pieces of state:

```c
typedef struct {
    float *storage;
    size_t size;
    size_t head;
    size_t count;
} RingBuffer;
```

### `storage`

Pointer to the externally allocated memory region used to store samples.

The Ring Buffer does not own this memory and therefore does not allocate or
free it.

### `size`

Total storage capacity, expressed as the number of samples that can be
stored.

### `head`

Index of the next position where a sample will be written.

After each insertion:

```text
head = (head + 1) % size
```

This provides the circular behaviour.

### `count`

Number of currently valid samples stored in the buffer.

Unlike `size`, which represents capacity, `count` represents the amount of
valid data currently available.

The following relationship must always hold:

```text
0 <= count <= size
```

---

## 4. API

The public API is:

```c
void rb_init(RingBuffer *rb, float *storage, size_t size);

void rb_push(RingBuffer *rb, float sample);

bool rb_get(const RingBuffer *rb, size_t i, float *out);
```

### `rb_init()`

Initializes a Ring Buffer using externally supplied storage.

The initial state is:

```text
head  = 0
count = 0
```

No samples are considered valid immediately after initialization.

### `rb_push()`

Stores a new sample at the current `head` position and advances `head`.

If the buffer is not full, `count` is incremented.

If the buffer is already full, `count` remains equal to `size` and the
new sample overwrites the oldest stored sample.

### `rb_get()`

Retrieves a sample relative to the most recently inserted sample.

The index is logical rather than a direct storage-array index:

```text
i = 0  -> most recent sample
i = 1  -> second most recent sample
i = 2  -> third most recent sample
...
```

The function returns:

```text
true  -> requested sample is valid and written to *out
false -> requested sample cannot be retrieved
```

---

## 5. Behaviour

### Initialization

Given a buffer with capacity 4:

```text
rb_init(...)
```

the resulting state is:

```text
storage = [?, ?, ?, ?]
head    = 0
count   = 0
```

No element may be retrieved because no samples have been stored yet.

---

### Push

For:

```text
push(10)
push(20)
push(30)
```

the state becomes:

```text
storage = [10, 20, 30, ?]
head    = 3
count   = 3
```

The logical order of valid samples is:

```text
30 -> 20 -> 10
```

Therefore:

```text
rb_get(0) -> 30
rb_get(1) -> 20
rb_get(2) -> 10
```

---

### Get

The logical sample index must satisfy:

```text
0 <= i < count
```

If this condition is satisfied, the corresponding sample is returned
through `out`.

The physical storage position is calculated using modular arithmetic:

```c
size_t index = (rb->head + rb->size - 1 - i) % rb->size;
```

This separates the logical ordering of samples from their physical
positions in memory.

---

### Full buffer

When the buffer reaches capacity:

```text
size  = 4
count = 4
```

additional pushes do not increase `count`.

Instead, the oldest sample is overwritten.

Example:

```text
push(10)
push(20)
push(30)
push(40)
push(50)
```

results in:

```text
storage = [50, 20, 30, 40]
head    = 2
count   = 4
```

The logical order is:

```text
50 -> 40 -> 30 -> 20
```

The buffer therefore always contains the four most recently inserted
samples.

---

### Partially filled buffer

When:

```text
count < size
```

each valid insertion increments `count` by one.

Unused storage positions do not represent valid samples and must not be
returned by `rb_get()`.

For example:

```text
size  = 4
count = 2
```

only:

```text
rb_get(0)
rb_get(1)
```

are valid.

---

### Invalid access

The following conditions result in a failed `rb_get()` operation:

- `rb == NULL`
- `rb->storage == NULL`
- `rb->size == 0`
- `out == NULL`
- `i >= rb->count`

In particular, an empty buffer has:

```text
count = 0
```

therefore:

```text
rb_get(0)
```

is invalid.

An index greater than or equal to `size` is also necessarily invalid,
because:

```text
count <= size
```

---

## 6. Design Decisions

### Why `count`?

The original implementation tracked only the storage capacity (`size`) and
the next write position (`head`).

This was insufficient to distinguish between:

1. storage positions containing valid samples;
2. storage positions that had not yet been written.

For example, immediately after initialization:

```text
storage = [?, ?, ?, ?]
head    = 0
```

The buffer cannot safely return any sample.

However, after:

```text
push(10)
```

the buffer contains exactly one valid sample.

The `count` field explicitly represents this state:

```text
count = 1
```

Therefore, `count` allows the implementation to distinguish between valid
and uninitialized portions of the storage array.

It also provides the invariant:

```text
0 <= count <= size
```

which can be used directly when validating sample access.

---

### Why `bool rb_get(...)`?

The original API returned the requested sample directly:

```c
float rb_get(RingBuffer *rb, size_t i);
```

This creates an ambiguity when an error occurs.

A floating-point sample may legitimately take any value within the supported
numeric range. Returning a special value such as:

```text
-9999.9
```

would therefore not provide a reliable error mechanism.

The API was changed to:

```c
bool rb_get(const RingBuffer *rb, size_t i, float *out);
```

The return value communicates the operation status:

```text
true  -> valid sample
false -> error
```

while `out` carries the actual sample value.

This separates **data** from **control/status information**.

---

### Why `const RingBuffer *`?

`rb_get()` only reads the Ring Buffer state and does not modify it.

Therefore, the function accepts:

```c
const RingBuffer *rb
```

This communicates the intended behaviour through the API and prevents the
function from accidentally modifying the Ring Buffer through that pointer.

It also allows the compiler to detect certain classes of unintended
modification.

---

## 7. Invariants

The implementation relies on the following invariants.

### Capacity

```text
size > 0
```

for a valid initialized buffer.

### Number of valid samples

```text
0 <= count <= size
```

### Write position

```text
0 <= head < size
```

### Valid logical access

```text
0 <= i < count
```

### Empty buffer

```text
count = 0
```

means that no sample can be retrieved.

### Full buffer

```text
count = size
```

means that all storage positions contain valid samples.

Once full, additional pushes preserve:

```text
count = size
```

while continuing to advance `head`.

---

## 8. Manual Validation

The updated implementation was first validated through manual state
tracking before automated tests were introduced.

For a buffer with:

```text
size = 4
```

the following sequence was analysed:

```text
push(10)
push(20)
push(30)
```

Result:

```text
storage = [10, 20, 30, ?]
head    = 3
count   = 3
```

Expected logical access:

```text
rb_get(0) -> 30
rb_get(1) -> 20
rb_get(2) -> 10
rb_get(3) -> invalid
```

After:

```text
push(40)
push(50)
```

the expected state is:

```text
storage = [50, 20, 30, 40]
head    = 2
count   = 4
```

Expected logical access:

```text
rb_get(0) -> 50
rb_get(1) -> 40
rb_get(2) -> 30
rb_get(3) -> 20
rb_get(4) -> invalid
```

This manual validation confirmed the expected relationship between
`storage`, `head`, `count`, and logical sample ordering.

Automated unit tests are required before considering the implementation
validated.

---

## 9. Open Questions / Future Improvements

The current implementation intentionally keeps the Ring Buffer simple and
focused on single-threaded DSP processing.

Potential future improvements include:

- Automated unit tests covering normal and boundary conditions.
- Improved error-reporting strategy for library code.
- Optional support for additional sample types.
- Consideration of a more generic or type-independent implementation.
- Performance benchmarking.
- Evaluation of whether the current API is suitable for embedded
  real-time DSP.
- Investigation of lock-free or thread-safe variants if required by a
  future streaming architecture.

These features are outside the current scope and should only be introduced
when justified by project requirements.