# Snake 3D OpenGL

Este projeto é uma animação 3D de uma cobra se movendo em um ambiente com árvores, chão, catedral e casas, utilizando OpenGL, SFML e SOIL.

## Estrutura de Pastas

A estrutura do projeto é organizada da seguinte forma:


## Arquivos Críticos

### 1. `include/`
Esta pasta contém os arquivos de cabeçalho para as diferentes partes do projeto.

- **audio.h**: Declarações para inicialização de áudio.
- **camera.h**: Declarações para controle de câmera.
- **environment.h**: Declarações para desenho de elementos do ambiente (chão, árvores, pilares).
- **models.h**: Declarações para carregamento e desenho de modelos STL.
- **snake.h**: Declarações para inicialização e atualização da cobra.
- **stl_loader.h**: Declarações para carregamento de arquivos STL.
- **textures.h**: Declarações para carregamento de texturas.

### 2. `src/`
Esta pasta contém os arquivos de implementação.

- **audio.cpp**: Implementação da inicialização de áudio.
- **camera.cpp**: Implementação do controle de câmera.
- **environment.cpp**: Implementação do desenho de elementos do ambiente.
- **main.cpp**: Ponto de entrada principal do programa, configurações de OpenGL e loop principal.
- **models.cpp**: Implementação do carregamento e desenho de modelos STL.
- **snake.cpp**: Implementação da inicialização e atualização da cobra.
- **stl_loader.cpp**: Implementação do carregamento de arquivos STL.
- **textures.cpp**: Implementação do carregamento de texturas.

### 3. `assets/`
Esta pasta contém os recursos necessários para a execução do programa, como texturas, modelos STL e arquivos de áudio.

- **arvore.png**: Textura da árvore.
- **groundTexture.bmp**: Textura do chão.
- **undergroundTexture.bmp**: Textura do subsolo.
- **skySide.bmp**: Textura lateral do céu.
- **skyTop.bmp**: Textura superior do céu.
- **Clermont-Ferrand_Cathedral.stl**: Modelo STL da catedral.
- **scaleable_base_door_and_roofv1_merged.stl**: Modelo STL das casas.
- **music2.ogg**: Arquivo de áudio.

### 4. `Makefile`
Arquivo de build que contém instruções para compilar e executar o projeto.

## Compilação e Execução

Para compilar e executar o projeto, siga os passos abaixo:

1. Navegue até o diretório do projeto.
2. Compile o projeto utilizando `make`:
   ```
   make
   ```


3. Execute o projeto:
   ```make run```