# Roadmap Técnico — Tomás
## Telecomunicações · RF · DSP · SDR · Redes · Embedded · Radar · EW · Defesa

**Objetivo terminal:** Estágio de Verão 2027 na TEKEVER (ou empresa equivalente — Thales, Leonardo, Airbus D&S, Indra, Rohde & Schwarz, Nokia)

**Perfil académico:** Eng. Eletrotécnica e de Computadores, FEUP, 3.º/4.º ano
**Constrangimento de tempo:** Estágio industrial 09:00–18:00 (seg-sex) → ~1–1.5h/dia úteis, fins de semana livres (4–6h/dia)

---

## Perfil de Partida (registo, 2026-08-04)

| Área | Nível |
|---|---|
| Eletromagnetismo | 16 val. |
| Fundamentos de Telecomunicações | 16 val. |
| Fundamentos de Proc. do Sinal | 15/16 val. |
| Ondas Eletromagnéticas | 12 val. |
| Python | Básico |
| C/C++ | Bases académicas (1.º ano), sem prática há ~3 anos |
| Git/GitHub | Básico, sem workflow estruturado |
| Hardware SDR/Embedded | Nenhum |

---

## Estrutura do Programa

```
Fase 0 — Setup de Engenharia               [2-3 semanas]   ← ESTÁS AQUI
Fase 1 — DSP Aplicado + SDR Fundamentals   [~2 meses]
Fase 2 — RF Engineering + Antenas/Micro-ondas   [~2-3 meses]
Fase 3 — Embedded Systems + Redes          [~2-3 meses]
Fase 4 — GNSS + Satélites                  [~1-2 meses]
Fase 5 — Radar + Electronic Warfare/SIGINT [~3 meses]
Fase 6 — Drones: comms links + integração  [~2 meses]
Fase 7 — FPGA (avançado)                   [~2-3 meses]
```

Timeline-alvo: portfólio com 2-3 projetos fortes (idealmente radar/EW, core da TEKEVER) visível e documentado até final de 2026, para candidaturas que tipicamente abrem entre out/2026–fev/2027.

---

# FASE 0 — Setup de Engenharia

## Objetivos

1. Reativar C/C++ a nível funcional (não académico — aplicado a DSP/embedded)
2. Estabelecer workflow de Git/GitHub de nível profissional
3. Montar stack de software completo para SDR/DSP
4. Produzir a primeira peça de portfólio, **sem depender de hardware**
5. Definir lista de compras para a Fase 1

## Competências a Adquirir

- Aritmética de vírgula fixa vs. flutuante (por que importa em embedded/FPGA)
- Estruturas de dados típicas de DSP em C (circular buffers, ring buffers)
- Git: branching (feature branches), conventional commits, `.gitignore`, README técnico, licenciamento
- Manipulação de dados IQ (I/Q samples) em Python/NumPy
- Leitura e escrita de formato SigMF (standard da indústria para datasets de RF)

## Stack de Software a Instalar

| Ferramenta | Propósito |
|---|---|
| Python 3.11+ + NumPy, SciPy, Matplotlib | Análise e prototipagem DSP |
| GNU Radio 3.10+ | Processamento de sinal em blocos, SDR |
| SDR++ | Visualização/receção SDR (quando tiveres hardware) |
| GCC/Clang + Make/CMake | Compilação C/C++ |
| STM32CubeIDE ou PlatformIO (VSCode) | Firmware STM32 (Fase 3, instalar já) |
| Git + GitHub CLI (`gh`) | Controlo de versão |
| Jupyter Lab | Notebooks de análise exploratória |

## Lista de Compras (para Fase 1, ~60-80€ total)

| Item | Referência sugerida | Preço aprox. | Propósito |
|---|---|---|---|
| SDR receiver | RTL-SDR Blog V4 (R828D + RTL2832U) | ~35-40€ | Receção wideband 500kHz-1.7GHz, standard de facto para aprendizagem |
| Antena | Dipolo telescópico + suporte, ou antena V incluída no kit | incluído/~10€ | Receção HF/VHF/UHF |
| Cabo SMA | SMA-M a SMA-M, 1-2m | ~5€ | Ligação a antenas externas |
| Dev board | STM32 Nucleo-F446RE | ~13€ | ARM Cortex-M4 com FPU — relevante para DSP embarcado |

**Nota de engenharia:** o RTL-SDR V4 usa um tuner R828D com melhor rejeição de imagem e cobertura HF direta (via direct sampling) comparado ao V3 — para trabalho sério em SIGINT/EW mais tarde, a diferença compensa o custo extra. Não compres HackRF/LimeSDR ainda: são ferramentas de TX, e vais precisar de dominar RX primeiro.

## Bibliografia

- **Lyons, R.** — *Understanding Digital Signal Processing* (3rd ed.) — capítulos 1-3 revistos em modo aplicado, não teórico
- **PySDR** — https://pysdr.org — recurso gratuito, orientado a Python, excelente ponte entre teoria e SDR prático
- **SigMF Specification** — https://github.com/sigmf/SigMF — formato standard para datasets IQ
- **Pro Git Book** (Chacon & Straub) — capítulos 3 (branching) e 7 (Git tools) — gratuito em git-scm.com

## Exercícios Técnicos

### Bloco C (reativação)
1. ✅ **[CONCLUÍDO — evoluído]** Buffer circular genérico em C puro — struct `RingBuffer` (`storage`, `size`, `head`, `count`), `rb_init`, `rb_push` (wraparound via módulo), `rb_get` (aritmética modular inversa, `head + size - 1 - i`), validação defensiva completa, include guard. **API refinada de forma autónoma**: `rb_get` passou de `float rb_get(...)` (0.0f em erro, ambíguo com amostra real igual a zero) para `bool rb_get(const RingBuffer *rb, size_t i, float *out)` — separa status de sucesso do valor devolvido, padrão C idiomático correto. Campo `count` adicionado para distinguir "capacidade total" de "amostras realmente escritas", evitando leitura de posições nunca inicializadas. Suite de testes própria em `tests/test_ring_buffer.c` (estado inicial, buffer vazio, push único, push múltiplo, wraparound, count/capacidade — 6 funções de teste, ~30 asserções).
2. ✅ **[CONCLUÍDO — recuperado após incidente]** Filtro FIR por convolução direta em C — struct `FirFilter` (reutiliza `RingBuffer` internamente como histórico), `fir_filter_init` (agora com `history_size` separado de `num_coefficients`, validação `history_size < num_coefficients`), `fir_filter_process`. Validado numericamente contra `scipy.signal.lfilter`. **Incidente registado (2026-08-13):** implementação foi apagada do repositório por decisão unilateral baseada num resumo de estado impreciso, depois de já estar validada e commitada — recuperada via `git checkout <hash> --`, sem perda de trabalho graças ao histórico Git. Lição: nunca agir sobre resumos de terceiros (incluindo gerados por IA) sem confirmar contra o estado real do repositório. Doxygen do `fir_filter_process` corrigido para descrever com precisão o mecanismo real (coeficientes sem amostra disponível são *ignorados* na soma, não há zero-padding explícito, ainda que o resultado numérico seja equivalente).
   - [ ] **Pendente:** testes automatizados de `fir_filter_process` (só `fir_filter_init` está testado em `tests/test_fir_filter.c` neste momento)
3. ⏸️ **[ADIADO — não esquecido]** Implementar a mesma convolução em aritmética de ponto fixo Q15, quantificar o erro face à versão float. Teoria já coberta (representação Q15, overflow na multiplicação Q15×Q15, trade-offs float vs. fixo). **Retomar antes da Fase 7 (FPGA)**, onde ponto fixo deixa de ser opcional.

### Bloco Python/DSP aplicado
4. 🔄 **[EM CURSO]** Análise IQ sobre gravação real de rádio FM (`fm_rds_250k_1Msamples.iq`, dataset PySDR, complex64, 250 kHz):
   - [x] Leitura do ficheiro raw + sanity check (`notebooks/iq_read_test.py`)
   - [x] PSD via método de Welch (`docs/fm_psd.png`) — largura de banda medida (~250 kHz) confirmada contra Regra de Carson
   - [ ] Espectrograma (STFT via `scipy.signal.spectrogram`) — próximo passo imediato
   - [ ] Identificação visual do tipo de modulação, justificada pela forma do espectro

### Bloco Git
5. Criar repositório `sdr-dsp-fundamentals` com: `README.md` técnico (motivação, arquitetura, como correr), `.gitignore` apropriado para Python+C, licença MIT, estrutura de pastas `/src`, `/docs`, `/tests`
6. Praticar workflow: criar feature branch por exercício, commits atómicos com mensagens no formato Conventional Commits (`feat:`, `fix:`, `docs:`), merge via PR (mesmo sozinho — simula prática de equipa)

## Mini-Desafio

Compara o tempo de execução do teu filtro FIR em C (compilado com `-O2`) vs. `scipy.signal.lfilter` vs. uma implementação Python pura (loop, sem NumPy) para um sinal de 1M de amostras. Documenta os resultados num pequeno relatório (`docs/benchmark.md`) e explica *porquê* das diferenças de performance (overhead de interpretação, vetorização SIMD do NumPy, otimização do compilador C).

## Projeto Fase 0 — "IQ Signal Analyzer"

Ferramenta em Python (CLI ou notebook) que:
- Lê ficheiros IQ em formato SigMF ou `.cfile` (complex64 raw)
- Calcula e visualiza: forma de onda no tempo, PSD, espectrograma
- Deteta automaticamente a largura de banda ocupada do sinal (threshold sobre a PSD)
- Inclui pelo menos um demodulador simples implementado por ti (ex: demodulação AM por deteção de envolvente)

Isto não precisa de hardware — usa datasets públicos. É a tua primeira entrada de portfólio: deve ter README com teoria resumida (o que é IQ sampling, por que se usa representação complexa em banda base), diagramas do pipeline de processamento, e resultados visuais.

## Critérios de Conclusão da Fase 0

- [x] C: buffer circular e filtro FIR funcionais, com testes que comparam contra SciPy
- [x] C: suite de testes automatizados para o ring buffer (`tests/test_ring_buffer.c`)
- [ ] C: suite de testes automatizados para o FIR filter (`tests/test_fir_filter.c` — só init está coberto)
- [ ] Ponto fixo: relatório curto sobre o erro de quantização Q15 vs float *(adiado para antes da Fase 7)*
- [x] Git: repositório com histórico de commits limpo, branches usadas corretamente (feature branches + PRs para cada função, mesmo sozinho)
- [ ] README.md do repositório atualizado e consistente com o estado real (pendente — desatualizado desde o incidente do FIR, urgente por candidatura TEKEVER ativa a referenciar o repo)
- [ ] Espectrograma + identificação de modulação (fecha o Exercício 4)
- [ ] Hardware da Fase 1 encomendado
- [x] Ambiente de desenvolvimento completo e testado (Python + venv, GCC, toolchain C)
- [x] Makefile no repositório (build simplificado, sem comando `gcc` manual)

## Nota — Estrutura do `src/` (decidida durante o desenvolvimento)

O código C está organizado como pequena biblioteca modular, uma pasta por componente:

```
src/
├── ring_buffer/
│   ├── ring_buffer.c
│   └── ring_buffer.h
└── fir_filter/
    ├── fir_filter.c
    └── fir_filter.h      (depende de ring_buffer/ring_buffer.h — FIR reutiliza o ring buffer como histórico)
tests/
├── test_ring_buffer.c
└── test_fir_filter.c
```

## Log de Progresso

| Data | Marco |
|---|---|
| 2026-08-04 | Setup inicial: perfil de partida registado, estrutura do repositório criada |
| ~2026-08 | Ring buffer completo (`rb_init`, `rb_push`, `rb_get`) — Exercício 1 fechado |
| ~2026-08 | Reorganização de `src/` em módulos (`ring_buffer/`, `fir_filter/`) |
| ~2026-08 | Filtro FIR completo, validado contra SciPy — Exercício 2 fechado |
| 2026-08-12 | Exercício 3 (Q15) adiado para antes da Fase 7; início do Exercício 4 (bloco Python, análise IQ) |
| 2026-08-12 | PSD (Welch) do sinal FM real concluída; largura de banda confirmada contra Regra de Carson |
| 2026-08-12 | CV e LinkedIn atualizados; candidatura Young Talent TEKEVER (SAR team) submetida |
| 2026-08-13 | **Incidente:** FIR filter apagado do repositório por decisão baseada em resumo impreciso — recuperado via Git sem perda de trabalho |
| 2026-08-13 | Refactor autónomo do ring buffer: `rb_get` passa a `bool` + parâmetro de saída, campo `count` adicionado; suites de teste criadas para ring buffer e (parcialmente) FIR filter |

---

# FASE 1 — DSP Aplicado + SDR Fundamentals
*(a detalhar quando Fase 0 estiver concluída — GNU Radio flowgraphs, receção real com RTL-SDR, demodulação AM/FM/SSB, deteção e classificação básica de sinais)*

# FASE 2 — RF Engineering + Antenas/Micro-ondas
*(a detalhar — linhas de transmissão aplicadas, Smith chart, matching networks, medições com VNA, projeto e caracterização de antena real)*

# FASE 3 — Embedded Systems + Redes
*(a detalhar — STM32 bare-metal e RTOS, protocolos de comunicação, LoRa, stack TCP/IP, telemetria)*

# FASE 4 — GNSS + Satélites
*(a detalhar — receção de sinais GNSS reais com SDR, tracking loops, órbitas, comunicações espaciais)*

# FASE 5 — Radar + Electronic Warfare / SIGINT
*(a detalhar — radar FMCW com SDR, ELINT passivo, deteção e classificação de sinais desconhecidos)*

# FASE 6 — Drones: Comms Links + Integração de Sistema
*(a detalhar — enlaces RF drone-GCS, telemetria, redundância, jamming/anti-jamming)*

# FASE 7 — FPGA (Avançado)
*(a detalhar — VHDL, DSP em hardware, pipelines de processamento em tempo real)*