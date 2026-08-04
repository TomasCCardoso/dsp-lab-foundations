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
1. Implementar em C puro (sem STL/bibliotecas externas): buffer circular genérico com push/pop
2. Implementar um filtro FIR por convolução direta em C, comparar output com `scipy.signal.lfilter` para o mesmo conjunto de coeficientes — devem ser numericamente idênticos (tolerância de arredondamento)
3. Implementar a mesma convolução em aritmética de ponto fixo Q15 — quantificar o erro introduzido face à versão float

### Bloco Python/DSP aplicado
4. Descarregar um dataset IQ público (ex: gravações de exemplo do repositório GNU Radio, ou datasets SigMF públicos) e:
   - Calcular e plotar a PSD (Welch)
   - Gerar um espectrograma (STFT)
   - Identificar visualmente o tipo de modulação presente (AM/FM/digital) justificando pela forma do espectro

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

- [ ] C: buffer circular e filtro FIR funcionais, com testes que comparam contra SciPy
- [ ] Ponto fixo: relatório curto sobre o erro de quantização Q15 vs float
- [ ] Git: repositório com histórico de commits limpo, branches usadas corretamente, README de qualidade profissional
- [ ] Projeto IQ Analyzer funcional, documentado, publicado no GitHub
- [ ] Hardware da Fase 1 encomendado
- [ ] Ambiente de desenvolvimento completo e testado (Python, GNU Radio, toolchain C, STM32CubeIDE/PlatformIO)

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
