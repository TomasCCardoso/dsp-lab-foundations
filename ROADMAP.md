# Roadmap Técnico — Tomás
## Telecomunicações · RF · DSP · SDR · Redes · Embedded · Radar · EW · Defesa

**Objetivo terminal:** Estágio de Verão 2027 na TEKEVER (ou equivalente — Thales, Leonardo, Airbus D&S, Indra, Rohde & Schwarz, Nokia).

**Perfil académico:** Eng. Eletrotécnica e de Computadores, FEUP, 3º/4º ano.
**Constrangimento de tempo:** estágio industrial 09:00–18:00 (seg-sex) → ~1–1.5h/dia úteis, fins de semana livres (4–6h).

**Nota sobre este documento:** este roadmap substitui uma versão anterior que continha afirmações de progresso não verificadas (análises Python, candidaturas, "incidentes" registados) que não correspondiam a trabalho real teu. A partir de agora, **só entra neste documento aquilo que foi mostrado — código, output, ou resultado concreto**. Nada de estado assumido. Se um item não tem evidência, fica marcado como não confirmado, não como feito.

---

## Estado Verificado (única fonte de verdade: ficheiros que me mostraste)

| Item | Estado | Evidência |
|---|---|---|
| `RingBuffer` (`ring_buffer.c/h`) — init, push, get, wraparound, validação defensiva | ✅ Implementado | Código revisto diretamente |
| Testes do Ring Buffer (`test_ring_buffer.c`) — init, empty, push, push múltiplo, wraparound, count/capacidade | ✅ Implementado, 6 funções de teste | Código revisto diretamente |
| `FirFilter` (`fir_filter.c/h`) — init com validação, convolução via ring buffer de histórico | ✅ Implementado | Código revisto diretamente |
| Testes do FIR (`test_fir_filter.c`) — init, histórico incompleto/completo, resposta ao impulso, resposta DC, resposta sinusoidal | ✅ Implementado, 6 funções de teste | Código revisto diretamente |
| Makefile | ⚠️ Existe, mas com bug conhecido (`test` não depende de `test_fir_filter`) | Código revisto diretamente |
| Correções da revisão de código (6 pontos: Makefile, `rb_init` inseguro, validação em `fir_filter_process`, módulo vs. potência de 2, idioma dos comentários, floats exatos nos testes) | ❌ Não confirmado | Ainda não me mostraste o diff |
| Qualquer análise em Python (PSD, espectrograma, IQ) | ❌ Não confirmado / eliminado por ti | Disseste que apagaste por não teres aprendido com esse código |
| Hardware (RTL-SDR, STM32) | ❌ Não confirmado | Nunca me mostraste prova de compra |
| GitHub — repo, README, workflow de branches/PRs | ⚠️ Repo existe (`dsp-lab-foundations`), conteúdo do README não verificado por mim agora | Confirmaste o link, não o conteúdo atual |
| Candidaturas (TEKEVER ou outras) | ❌ Não verificado neste documento | Fora do âmbito do que posso confirmar |

Tudo o resto abaixo é plano, não histórico.

---

## Estrutura do Programa

```
Fase 0 — Fundações em C (DSP)              [EM CURSO — ~70% feito]
Fase 1 — DSP Aplicado em Python + GNU Radio [PRÓXIMA]
Fase 2 — SDR com Hardware (RTL-SDR)
Fase 3 — Embedded RF/DSP (STM32)
Fase 4 — Redes & Enlaces (TCP/IP, LoRa, telemetria)
Fase 5 — Antenas, Micro-ondas & GNSS
Fase 6 — Radar
Fase 7 — SIGINT/ELINT & Electronic Warfare (introdução)
Fase 8 — FPGA (avançado)
```

---

## FASE 0 — Fundações em C (DSP)

### Já feito (verificado)
Ring buffer e filtro FIR em C, ambos com testes unitários próprios cobrindo casos normais e de fronteira (wraparound, histórico incompleto, resposta impulsiva/DC/sinusoidal). Isto é uma base sólida — a maior parte dos estudantes do teu ano nunca escreveu um FIR filter em C com testes.

### Falta para fechar a fase
1. **Corrigir os 6 pontos da revisão de código** (Makefile, `rb_init` que deixa struct indefinido em erro, falta de validação em `fir_filter_process`, módulo vs. bitmask para potências de 2, comentários em inglês consistente, comparação exata de floats nos testes). Traz-me o diff quando estiver feito — reviso outra vez.
2. **Ponto fixo Q15** — implementa a mesma convolução FIR em aritmética Q15 e mede o erro de quantização face à versão float. Isto não é opcional mais tarde: FPGA (Fase 8) trabalha em ponto fixo por defeito.
3. **README.md do repositório** — estado atual, não aspiracional. Escreve-o tu, sem IA a gerar o texto todo; eu reviso depois.

### Critério de conclusão da Fase 0
- [ ] 6 pontos da revisão corrigidos e confirmados
- [ ] Q15 implementado com relatório curto de erro de quantização
- [ ] README.md reflete o estado real do repo
- [ ] `make test` corre limpo do zero (`make clean && make test`)

---

## FASE 1 — DSP Aplicado em Python + GNU Radio

**Só começa depois da Fase 0 fechada.** Não adianta avançar para Python enquanto o C tem correções pendentes — hábito de deixar dívida técnica para trás é o oposto do que queremos construir.

### Objetivos
- Traduzir teoria de Fourier/amostragem/filtros em implementação testada, não em notebooks soltos
- Trabalhar com dados IQ reais (não simulados) desde o início

### Competências
- Design de filtros (janelamento, Parks-McClellan) e trade-offs
- STFT/espectrograma implementado à mão (sem `scipy.signal.spectrogram` como caixa preta primeiro)
- Demodulação digital básica (BPSK) com cadeia completa: mapper → pulse shaping → canal AWGN → matched filter → decisor
- GNU Radio Companion: flowgraphs, blocos custom em Python

### Bibliografia
- Lyons, *Understanding Digital Signal Processing* (3ª ed.)
- PySDR (pysdr.org)
- Rice, *Digital Communications: A Discrete-Time Approach*

### Projeto da fase
Espectrograma manual + identificação de sub-portadoras num sinal FM/RDS real, seguido de demodulador FM por discriminador de quadratura implementado do zero — **exatamente o exercício que estás a fazer agora, 11h–13h**. Quando trouxeres o resultado, reviso com o mesmo rigor do C, e só aí este item entra como "verificado" no roadmap.

### Critério de conclusão
- Espectrograma manual validado contra `scipy.signal.spectrogram` (erro documentado)
- Sub-portadoras FM/RDS localizadas com erro percentual calculado, não "a olho"
- Demodulador de quadratura funcional, banda ocupada do sinal demodulado confirmada pela regra de Carson
- Relatório em `docs/` no mesmo estilo do `ring-buffer.md`

---

## FASE 2 — SDR com Hardware (RTL-SDR)

*(a detalhar quando a Fase 1 estiver fechada — depende de decisão de compra de hardware ainda não confirmada)*

## FASE 3 — Embedded RF/DSP (STM32)

*(a detalhar — depende de aquisição de placa Nucleo, ainda não confirmada)*

## FASE 4 — Redes & Enlaces (TCP/IP, LoRa, telemetria)

*(a detalhar)*

## FASE 5 — Antenas, Micro-ondas & GNSS

*(a detalhar)*

## FASE 6 — Radar

*(a detalhar)*

## FASE 7 — SIGINT/ELINT & Electronic Warfare (introdução)

*(a detalhar — sempre enquadrado em contexto legal/ético explícito)*

## FASE 8 — FPGA (avançado)

*(a detalhar)*

---

## Regra de manutenção deste documento

Só se marca algo como concluído quando eu (ou outra revisão externa) vir o código, o output, ou o resultado — nunca com base num resumo, teu ou meu. Se um AI (eu incluído) gerar uma secção de progresso sem teres mostrado prova, apaga-a. É a mesma disciplina que já aplicaste ao apagar o Python que não tinha sido aprendizagem tua — mantém-na aqui também.