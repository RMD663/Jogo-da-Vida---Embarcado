# Jogo da Vida - Raspberry Pi Pico

Este projeto implementa o **Jogo da Vida de Conway** em um Raspberry Pi Pico, utilizando um display OLED SSD1306 e controles por botões.

## 📋 Descrição

O Jogo da Vida é um autômato celular desenvolvido pelo matemático John Horton Conway. Esta implementação inclui:

- Simulação do Jogo da Vida em tempo real
- Display gráfico com células vivas e mortas
- Efeitos sonoros e visuais
- Controles interativos via botões
- Animações de início e fim

## 🛠 Hardware Requerido

- **Raspberry Pi Pico** ou **Pico W**
- **Display OLED SSD1306** (128x64 pixels, I2C)
- **2 Botões** para controle
- **2 Buzzers** para efeitos sonoros
- **LED vermelho** para indicador de fim de jogo

### Pinagem

| Componente | GPIO |
|------------|------|
| Display OLED (SDA) | GPIO 14 |
| Display OLED (SCL) | GPIO 15 |
| Botão A | GPIO 5 |
| Botão B | GPIO 6 |
| Buzzer A | GPIO 10 |
| Buzzer B | GPIO 21 |
| LED Vermelho | GPIO 13 |

## 🎮 Funcionalidades

### Controles
- **Botão A**: Reiniciar a simulação
- **Botão B**: Pausar/continuar a simulação

### Características do Jogo
- Grid de 64×32 células (exibidas com tamanho 2×2 pixels)
- Geração aleatória inicial de células
- Detecção automática quando todas as células morrem
- Limite de 1000 gerações

### Efeitos Especiais
- **Splash screen** com animação e sons
- **Efeitos sonoros** para diferentes eventos
- **Mensagens** informativas no display
- **LED indicador** quando o jogo termina

## 📁 Estrutura do Projeto

```
JogoDaVidaFinal/
├── CMakeLists.txt
├── JogoDaVidaFinal.c          # Arquivo principal
├── inc/
│   ├── GameOfLife.h           # Cabeçalho principal
│   ├── GameOfLife.c           # Implementação da lógica do jogo
│   └── EmbarcaLogo.h          # Logo e recursos gráficos
└── libs/
    └── ssd1306/
        ├── ssd1306.h          # Driver do display OLED
        ├── ssd1306.c          # Implementação do driver
        └── font.h             # Fonte para texto
```

## 🔧 Compilação e Instalação

### Pré-requisitos
- Raspberry Pi Pico SDK
- CMake
- Toolchain ARM

### Compilação
```bash
mkdir build
cd build
cmake ..
make
```

### Instalação
1. Conecte o Raspberry Pi Pico no modo BOOTSEL
2. Copie o arquivo `JogoDaVidaFinal.uf2` para a unidade montada

## 🎵 Sons Implementados

- **Som de introdução**: Tocado durante a splash screen
- **Som do logo**: Efeito musical para identidade visual
- **Som de reset**: Alerta quando o jogo é reiniciado
- **Som de fim**: Indicador quando a simulação termina

## ⚙️ Configurações

### Parâmetros Ajustáveis
```c
#define CELL_SIZE 2            # Tamanho de cada célula em pixels
#define GRID_WIDTH 64          # Largura do grid em células
#define GRID_HEIGHT 32         # Altura do grid em células
```

## 🚀 Como Usar

1. **Inicialização**: O jogo inicia com uma animação e sons
2. **Simulação**: As células evoluem automaticamente
3. **Controles**:
   - Pressione **Botão B** para pausar/continuar
   - Pressione **Botão A** para reiniciar com nova população
4. **Fim do Jogo**: Ocorre quando todas as células morrem ou após 1000 gerações

## 🔄 Fluxo do Programa

1. Inicialização de hardware e display
2. Animação de splash screen
3. Geração aleatória inicial
4. Loop principal de simulação
5. Verificação de controles e condições de término
6. Sequência de finalização com mensagens e sons

## 🐛 Solução de Problemas

- **Display não funciona**: Verifique conexões I2C e endereço (0x3C)
- **Botões não respondem**: Confirme a configuração de pull-up
- **Sem som**: Verifique os buzzers e a pinagem GPIO

## 📄 Licença

Este projeto utiliza bibliotecas sob licença MIT e foi desenvolvido para fins educacionais.

---

**Desenvolvido por Ryan Mesquita para Embarca Tech 2025**
