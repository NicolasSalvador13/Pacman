#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Ghost {
    public:
    int blocoX, blocoY; // Posição do fantasma em blocos
    int dirX, dirY;     // Direção atual
    float posX, posY;
    bool vivo;
    bool visivel;
    bool fantasmaolhadireita = true;
    bool fantasmaolhaesquerda = false;
    bool fantasmaolhacima = false;
    bool fantasmaolhabaixo = false;
    sf::Sprite spriteDir, spriteEsq, spriteCima, spriteBaixo;

    Ghost(int x, int y, 
        const sf::Sprite& sprDir, const sf::Sprite& sprEsq, 
        const sf::Sprite& sprCima, const sf::Sprite& sprBaixo,
        float tamanho_bloco) 
    {
        blocoX = x;
        blocoY = y;
        posX = x * tamanho_bloco; // Inicialização visual
        posY = y * tamanho_bloco;
        dirX = 0;
        dirY = 0;
        vivo = true;
        visivel = true;
        spriteDir = sprDir;
        spriteEsq = sprEsq;
        spriteCima = sprCima;
        spriteBaixo = sprBaixo;
    }

    void movimento_aleatorio(char mapa[30][29]) {
        // Só muda de direção se estiver alinhado na grade (sempre está, pois só move em blocos)
        std::vector<std::pair<int, int>> direcoes = { {1,0}, {-1,0}, {0,1}, {0,-1} };
        // Remove a direção oposta à atual, se possível
        direcoes.erase(std::remove_if(direcoes.begin(), direcoes.end(),
            [this](const std::pair<int,int>& d) {
                return (d.first == -dirX && d.second == -dirY);
            }), direcoes.end());
        // Embaralha as direções
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(direcoes.begin(), direcoes.end(), g);
        // Tenta cada direção aleatória até achar uma livre
        for (auto& d : direcoes) {
            int novoX = blocoX + d.first;
            int novoY = blocoY + d.second;
            if (novoX >= 0 && novoX < 28 && novoY >= 0 && novoY < 30 && mapa[novoY][novoX] != '1') {
                dirX = d.first;
                dirY = d.second;
                return;
            }
        }
        // Se não encontrou nenhuma direção livre, para
        dirX = 0;
        dirY = 0;
    }

    void mover(char mapa[30][29]) {
        int proxX = blocoX + dirX;
        int proxY = blocoY + dirY;
        if (dirX == 0 && dirY == 0) return; // parado
        if (proxX >= 0 && proxX < 28 && proxY >= 0 && proxY < 30 && mapa[proxY][proxX] != '1') {
            blocoX = proxX;
            blocoY = proxY;
        } else {
            dirX = 0;
            dirY = 0;
        }
    }

    void desenhar(sf::RenderWindow& window, float tamanho_bloco, float centralizar) {
        if (!visivel) return;
        // Atualiza a direção visual automaticamente
        if (dirX > 0) {
            fantasmaolhadireita = true;
            fantasmaolhaesquerda = fantasmaolhacima = fantasmaolhabaixo = false;
        } else if (dirX < 0) {
            fantasmaolhaesquerda = true;
            fantasmaolhadireita = fantasmaolhacima = fantasmaolhabaixo = false;
        } else if (dirY < 0) {
            fantasmaolhacima = true;
            fantasmaolhadireita = fantasmaolhaesquerda = fantasmaolhabaixo = false;
        } else if (dirY > 0) {
            fantasmaolhabaixo = true;
            fantasmaolhadireita = fantasmaolhaesquerda = fantasmaolhacima = false;
        }
        float px = posX + centralizar;
        float py = posY + centralizar;
        if (fantasmaolhadireita) {
            spriteDir.setPosition(px, py);
            window.draw(spriteDir);
        } else if (fantasmaolhaesquerda) {
            spriteEsq.setPosition(px, py);
            window.draw(spriteEsq);
        } else if (fantasmaolhacima) {
            spriteCima.setPosition(px, py);
            window.draw(spriteCima);
        } else if (fantasmaolhabaixo) {
            spriteBaixo.setPosition(px, py);
            window.draw(spriteBaixo);
        } else {
            spriteDir.setPosition(px, py);
            window.draw(spriteDir);
        }
    }

    void resetar() {
        blocoX = 14;
        blocoY = 15;
        vivo = true;
        visivel = true;
        dirX = 0;
        dirY = 0;
    }
};

char mapa[30][29] = {
	// 1 = parede, 0 = comida, 3 = poder, 4 = banana, 5 = morango, 6 = cereja, 2 = tunel
    "1111111111111111111111111111",
    "1000000000000110000000003001",
    "1011110111110110111110111101",
    "1611110111110110111110111101",
    "1011110111110110111110111101",
    "1000200000000004000030000001",
    "1011110110111111110110111101",
    "1011110110111111110110111101",
    "1000000113000110000110000051",
    "1111110111110110111110111111",
    "1111110111110110111110111111",
    "1111114112222222222110111111",
    "1111110112111221112113111111",
    "1111113112122222212110111111",
    "2222220222122222212220222222",
    "1111110112122222212110111111",
    "1111110112111111112110111111",
    "1111110112222222222110111111",
    "1111110112111111112110111111",
    "1000000000000110000000000001",
    "1011110111110110111110111101",
    "1011110111110110111110111101",
    "1000110000000000000000110001",
    "1110110110111111110110115111",
    "1110110110111111110110110111",
    "1300000110000110000110000001",
    "1011111111110110111111111101",
    "1011111111110110111111111131",
    "1006000000300000000000000001",
    "1111111111111111111111111111"
};

int posx = 4, posy = 5;     // Posicao inicial do pacman
bool cima = false, baixo = false, esq = false, dir = false;     // Booleanos para controle da movimentacao
bool int_cima = false, int_baixo = false, int_esq = false, int_dir = false; // Variaveis para controle da intencao de movimentacao

bool olhadireita = true;
bool olhaesquerda = false;
bool olhacima = false;
bool olhabaixo = false;

int main() {
	int vidas = 3;  // Variavel para armazenar o numero de vidas
	int score = 0;  // Variavel para armazenar a pontuacao
	float tamanho_bloco = 28;  // Tamanho do bloco em pixels
	float fator_pacman = 0.85f; // Fator de controle do tamanho do pacman
	float raio_comida = 3.f;  // Raio da comida
	float raio_poder = 8.f;  // Raio do poder
	float centralizar_comida = (tamanho_bloco / 2.0f) - raio_comida;  // constante para centralizar a comida
	float centralizar_poder = (tamanho_bloco / 2.0f) - raio_poder;  // constante para centralizar o poder

    float tamanho_pacman_real = tamanho_bloco * fator_pacman;   // Regula tamanho do pacman
	float centralizar = (tamanho_bloco - tamanho_pacman_real) / 2.0f;  // constante para centralizar o pacman

    float pacmanX = posx * tamanho_bloco;       // Posicao do pacman em pixels na horizontal
    float pacmanY = posy * tamanho_bloco;       // Posicao do pacman em pixels na vertical
    float velocidade = 100.f; // pixels por segundo

	int largura_janela_total = tamanho_bloco * 28;      // Largura total da janela
	int altura_janela_total = tamanho_bloco * 30 + 80;      // Altura total da janela (30 blocos + 80 pixels para a pontuacao e vidas)

	// Criacao da janela
    sf::RenderWindow window(sf::VideoMode(largura_janela_total, altura_janela_total), "Pac-Man");
    window.setFramerateLimit(60);

	// Criacao dos objetos graficos
    // Paredes, comida e poder
    sf::RectangleShape rectangle(sf::Vector2f(tamanho_bloco, tamanho_bloco));
    rectangle.setFillColor(sf::Color(0, 35, 102));

    sf::CircleShape comida(raio_comida);
    comida.setFillColor(sf::Color(204, 169, 221));

    sf::CircleShape poder(raio_poder);
    poder.setFillColor(sf::Color::White);

	// Carregar a fonte para o texto
    sf::Font font;
    if (!font.loadFromFile("Oxanium-ExtraBold.ttf")) {
        cout << "Erro: Nao foi possivel carregar a fonte!" << endl;
        return 1;
    }

	// Configurar o texto de pontuacao
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: 0");
	sf::FloatRect textRect = scoreText.getLocalBounds();  // Obtém o retangulo delimitador do texto
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);  // Centraliza o texto
	float centerX = largura_janela_total / 2.0f;    // Centraliza o texto na largura da janela
	float centerY = 20.0f;      // Centraliza o texto na altura da janela
	scoreText.setPosition(centerX - 5, centerY - 5);    // <-- Ajuste de posicao para centralizar o texto

    // --- Carregamento de todas as texturas dos fantasmas ---

    // Fantasma vermelho (o original do seu exemplo)
    sf::Texture texturefantasmavermelho;
    if (!texturefantasmavermelho.loadFromFile("fantasmavermelho.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma vermelho
    sf::Sprite spritefantasmavermelho;
    spritefantasmavermelho.setTexture(texturefantasmavermelho);
    spritefantasmavermelho.setScale(tamanho_pacman_real / texturefantasmavermelho.getSize().x, tamanho_pacman_real / texturefantasmavermelho.getSize().y);   // Controla tamanho do fantasma

    // Fantasma vermelho para baixo
    sf::Texture texturefantasmavermelhobaixo;
    if (!texturefantasmavermelhobaixo.loadFromFile("fantasmavermelhobaixo.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma vermelho para baixo
    sf::Sprite spritefantasmavermelhobaixo;
    spritefantasmavermelhobaixo.setTexture(texturefantasmavermelhobaixo);
    spritefantasmavermelhobaixo.setScale(tamanho_pacman_real / texturefantasmavermelhobaixo.getSize().x, tamanho_pacman_real / texturefantasmavermelhobaixo.getSize().y);   // Controla tamanho do fantasma

    // Fantasma vermelho para cima
    sf::Texture texturefantasmavermelhocima;
    if (!texturefantasmavermelhocima.loadFromFile("fantasmavermelhocima.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma vermelho para cima
    sf::Sprite spritefantasmavermelhocima;
    spritefantasmavermelhocima.setTexture(texturefantasmavermelhocima);
    spritefantasmavermelhocima.setScale(tamanho_pacman_real / texturefantasmavermelhocima.getSize().x, tamanho_pacman_real / texturefantasmavermelhocima.getSize().y);   // Controla tamanho do fantasma

    // Fantasma vermelho para esquerda
    sf::Texture texturefantasmavermelhoesquerda;
    if (!texturefantasmavermelhoesquerda.loadFromFile("fantasmavermelhoesquerda.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma vermelho para esquerda
    sf::Sprite spritefantasmavermelhoesquerda;
    spritefantasmavermelhoesquerda.setTexture(texturefantasmavermelhoesquerda);
    spritefantasmavermelhoesquerda.setScale(tamanho_pacman_real / texturefantasmavermelhoesquerda.getSize().x, tamanho_pacman_real / texturefantasmavermelhoesquerda.getSize().y);   // Controla tamanho do fantasma

    // Fantasma amarelo
    sf::Texture texturefantasmaamarelo;
    if (!texturefantasmaamarelo.loadFromFile("fantasmaamarelo.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma amarelo
    sf::Sprite spritefantasmaamarelo;
    spritefantasmaamarelo.setTexture(texturefantasmaamarelo);
    spritefantasmaamarelo.setScale(tamanho_pacman_real / texturefantasmaamarelo.getSize().x, tamanho_pacman_real / texturefantasmaamarelo.getSize().y);   // Controla tamanho do fantasma

    // Fantasma amarelo para baixo
    sf::Texture texturefantasmaamarelobaixo;
    if (!texturefantasmaamarelobaixo.loadFromFile("fantasmaamarelobaixo.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma amarelo para baixo
    sf::Sprite spritefantasmaamarelobaixo;
    spritefantasmaamarelobaixo.setTexture(texturefantasmaamarelobaixo);
    spritefantasmaamarelobaixo.setScale(tamanho_pacman_real / texturefantasmaamarelobaixo.getSize().x, tamanho_pacman_real / texturefantasmaamarelobaixo.getSize().y);   // Controla tamanho do fantasma

    // Fantasma amarelo para cima
    sf::Texture texturefantasmaamarelocima;
    if (!texturefantasmaamarelocima.loadFromFile("fantasmaamarelocima.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma amarelo para cima
    sf::Sprite spritefantasmaamarelocima;
    spritefantasmaamarelocima.setTexture(texturefantasmaamarelocima);
    spritefantasmaamarelocima.setScale(tamanho_pacman_real / texturefantasmaamarelocima.getSize().x, tamanho_pacman_real / texturefantasmaamarelocima.getSize().y);   // Controla tamanho do fantasma

    // Fantasma amarelo para esquerda
    sf::Texture texturefantasmaamareloesquerda;
    if (!texturefantasmaamareloesquerda.loadFromFile("fantasmaamareloesquerda.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma amarelo para esquerda
    sf::Sprite spritefantasmaamareloesquerda;
    spritefantasmaamareloesquerda.setTexture(texturefantasmaamareloesquerda);
    spritefantasmaamareloesquerda.setScale(tamanho_pacman_real / texturefantasmaamareloesquerda.getSize().x, tamanho_pacman_real / texturefantasmaamareloesquerda.getSize().y);   // Controla tamanho do fantasma

    // Fantasma rosa
    sf::Texture texturefantasmarosa;
    if (!texturefantasmarosa.loadFromFile("fantasmarosa.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma rosa
    sf::Sprite spritefantasmarosa;
    spritefantasmarosa.setTexture(texturefantasmarosa);
    spritefantasmarosa.setScale(tamanho_pacman_real / texturefantasmarosa.getSize().x, tamanho_pacman_real / texturefantasmarosa.getSize().y);   // Controla tamanho do fantasma

    // Fantasma rosa para cima
    sf::Texture texturefantasmarosacima;
    if (!texturefantasmarosacima.loadFromFile("fantasmarosacima.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma rosa para cima
    sf::Sprite spritefantasmarosacima;
    spritefantasmarosacima.setTexture(texturefantasmarosacima);
    spritefantasmarosacima.setScale(tamanho_pacman_real / texturefantasmarosacima.getSize().x, tamanho_pacman_real / texturefantasmarosacima.getSize().y);   // Controla tamanho do fantasma

    // Fantasma rosa para esquerda
    sf::Texture texturefantasmarosaesquerda;
    if (!texturefantasmarosaesquerda.loadFromFile("fantasmarosaesquerda.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma rosa para esquerda
    sf::Sprite spritefantasmarosaesquerda;
    spritefantasmarosaesquerda.setTexture(texturefantasmarosaesquerda);
    spritefantasmarosaesquerda.setScale(tamanho_pacman_real / texturefantasmarosaesquerda.getSize().x, tamanho_pacman_real / texturefantasmarosaesquerda.getSize().y);   // Controla tamanho do fantasma

    // Fantasma rosa para baixo
    sf::Texture texturefantasmarosabaixo;
    if (!texturefantasmarosabaixo.loadFromFile("fantasmarosabaixo.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma rosa para baixo
    sf::Sprite spritefantasmarosabaixo;
    spritefantasmarosabaixo.setTexture(texturefantasmarosabaixo);
    spritefantasmarosabaixo.setScale(tamanho_pacman_real / texturefantasmarosabaixo.getSize().x, tamanho_pacman_real / texturefantasmarosabaixo.getSize().y);   // Controla tamanho do fantasma

    // Fantasma azul
    sf::Texture texturefantasmaazul;
    if (!texturefantasmaazul.loadFromFile("fantasmaazul.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma azul
    sf::Sprite spritefantasmaazul;
    spritefantasmaazul.setTexture(texturefantasmaazul);
    spritefantasmaazul.setScale(tamanho_pacman_real / texturefantasmaazul.getSize().x, tamanho_pacman_real / texturefantasmaazul.getSize().y);   // Controla tamanho do fantasma

    // Fantasma azul para baixo
    sf::Texture texturefantasmaazulbaixo;
    if (!texturefantasmaazulbaixo.loadFromFile("fantasmaazulbaixo.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma azul para baixo
    sf::Sprite spritefantasmaazulbaixo;
    spritefantasmaazulbaixo.setTexture(texturefantasmaazulbaixo);
    spritefantasmaazulbaixo.setScale(tamanho_pacman_real / texturefantasmaazulbaixo.getSize().x, tamanho_pacman_real / texturefantasmaazulbaixo.getSize().y);   // Controla tamanho do fantasma

    // Fantasma azul para esquerda
    sf::Texture texturefantasmaazulesquerda;
    if (!texturefantasmaazulesquerda.loadFromFile("fantasmaazulesquerda.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma azul para esquerda
    sf::Sprite spritefantasmaazulesquerda;
    spritefantasmaazulesquerda.setTexture(texturefantasmaazulesquerda);
    spritefantasmaazulesquerda.setScale(tamanho_pacman_real / texturefantasmaazulesquerda.getSize().x, tamanho_pacman_real / texturefantasmaazulesquerda.getSize().y);   // Controla tamanho do fantasma

    // Fantasma azul para cima
    sf::Texture texturefantasmaazulcima;
    if (!texturefantasmaazulcima.loadFromFile("fantasmaazulcima.png")) { return 1; } // Caso nao consiga carregar a textura do fantasma azul para cima
    sf::Sprite spritefantasmaazulcima;
    spritefantasmaazulcima.setTexture(texturefantasmaazulcima);
    spritefantasmaazulcima.setScale(tamanho_pacman_real / texturefantasmaazulcima.getSize().x, tamanho_pacman_real / texturefantasmaazulcima.getSize().y);   // Controla tamanho do fantasma

    //Tamanho banana
    sf::Texture texturebanana;
	if (!texturebanana.loadFromFile("banana.png")) { return 1; }    // Caso nao consiga carregar a textura da banana
    sf::Sprite spritebanana;
    spritebanana.setTexture(texturebanana);
	spritebanana.setScale(tamanho_pacman_real / texturebanana.getSize().x, tamanho_pacman_real / texturebanana.getSize().y);    // Controla tamanho da banana

    //Tamanho morango
    sf::Texture texturemorango;
	if (!texturemorango.loadFromFile("morango.png")) { return 1; }  // Caso nao consiga carregar a textura do morango
    sf::Sprite spritemorango;
    spritemorango.setTexture(texturemorango);
    spritemorango.setScale(tamanho_pacman_real / texturemorango.getSize().x, tamanho_pacman_real / texturemorango.getSize().y);

    //Tamanho cereja
    sf::Texture texturecereja;
    if (!texturecereja.loadFromFile("cereja.png")) { return 1; }
    sf::Sprite spritecereja;
    spritecereja.setTexture(texturecereja);
    spritecereja.setScale(tamanho_pacman_real / texturecereja.getSize().x, tamanho_pacman_real / texturecereja.getSize().y);

    //pac man direita
    sf::Texture textureDir;
    if (!textureDir.loadFromFile("pacman.png")) { return 1; }       // Caso nao consiga carregar a textura do pacman
    sf::Sprite spriteDir;
    spriteDir.setTexture(textureDir);
    spriteDir.setScale(tamanho_pacman_real / textureDir.getSize().x, tamanho_pacman_real / textureDir.getSize().y);

    //pacmanesquerda
    sf::Texture textureEsq;
    if (!textureEsq.loadFromFile("pacman-esq.png")) { return 1; }
    sf::Sprite spriteEsq;
    spriteEsq.setTexture(textureEsq);
    spriteEsq.setScale(tamanho_pacman_real / textureEsq.getSize().x, tamanho_pacman_real / textureEsq.getSize().y);

    //pacmancima
    sf::Texture textureCima;
    if (!textureCima.loadFromFile("pacmancima.png")) { return 1; }
    sf::Sprite spriteCima;
    spriteCima.setTexture(textureCima);
    spriteCima.setScale(tamanho_pacman_real / textureCima.getSize().x, tamanho_pacman_real / textureCima.getSize().y);

    //pacmanbaixo
    sf::Texture textureBaixo;
    if (!textureBaixo.loadFromFile("pacmanbaixo.png")) { return 1; }
    sf::Sprite spriteBaixo;
    spriteBaixo.setTexture(textureBaixo);
    spriteBaixo.setScale(tamanho_pacman_real / textureBaixo.getSize().x, tamanho_pacman_real / textureBaixo.getSize().y);

    // Criacao dos fantasmas
    Ghost fantasmaVermelho(
        13, 14, // posição em blocos
        spritefantasmavermelho, spritefantasmavermelhoesquerda,
        spritefantasmavermelhocima, spritefantasmavermelhobaixo,
        tamanho_bloco
    );

    Ghost fantasmaAmarelo(
        14, 14, // posição em blocos
        spritefantasmaamarelo, spritefantasmaamareloesquerda,
        spritefantasmaamarelocima, spritefantasmaamarelobaixo,
        tamanho_bloco
    );

    Ghost fantasmaRosa(
        15, 14, // posição em blocos
        spritefantasmarosa, spritefantasmarosaesquerda,
        spritefantasmarosacima, spritefantasmarosabaixo,
        tamanho_bloco
    );

    Ghost fantasmaAzul(
        16, 14, // posição em blocos
        spritefantasmaazul, spritefantasmaazulesquerda,
        spritefantasmaazulcima, spritefantasmaazulbaixo,
        tamanho_bloco
    );

    sf::Clock clock;
	sf::Clock deltaClock; // Relogio para controlar o tempo de movimento suave
    sf::Clock ghostClock;
    float ghostDelay = 0.2f; // tempo em segundos entre cada movimento do fantasma (aumente para mais lento)
	// Variaveis para controlar a direcao
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        
            // Verifica se uma tecla foi pressionada e atualiza as intenções de movimento
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    int_esq = true; int_dir = int_cima = int_baixo = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    int_dir = true; int_esq = int_cima = int_baixo = false;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    int_cima = true; int_esq = int_dir = int_baixo = false;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    int_baixo = true; int_esq = int_dir = int_cima = false;
                }
            }
        }

        if (clock.getElapsedTime() > sf::seconds(0.01)) { // Reduz o tempo para suavizar
            clock.restart();
            const int LINHA_DO_TUNEL = 14;

            // Verifica se o Pac-Man está alinhado na grade
            // Função fmod retorna o resto da divisao, se for 0, significa que está alinhado
            bool alinhado = (fmod(pacmanX, tamanho_bloco) == 0) && (fmod(pacmanY, tamanho_bloco) == 0);

            if (alinhado) {
                // Atualiza posx e posy para garantir que estão corretos
                posx = (int)(pacmanX / tamanho_bloco);
                posy = (int)(pacmanY / tamanho_bloco);

                // Atualiza direção real com base na intenção, se possível
                if (int_cima && posy > 0 && mapa[posy - 1][posx] != '1') {
                    cima = true; baixo = esq = dir = false;
                    olhacima = true; olhadireita = olhaesquerda = olhabaixo = false;
                }
                else if (int_baixo && posy < 29 && mapa[posy + 1][posx] != '1') {
                    baixo = true; cima = esq = dir = false;
                    olhabaixo = true; olhadireita = olhaesquerda = olhacima = false;
                }
                else if (int_esq && ((posx > 0 && mapa[posy][posx - 1] != '1') || (posx == 0 && posy == 14))) {
                    esq = true; dir = cima = baixo = false;
                    olhaesquerda = true; olhadireita = olhacima = olhabaixo = false;
                }
                else if (int_dir && ((posx < 27 && mapa[posy][posx + 1] != '1') || (posx == 27 && posy == 14))) {
                    dir = true; esq = cima = baixo = false;
                    olhadireita = true; olhaesquerda = olhacima = olhabaixo = false;
                }
            }

            // Atualize a posição suavemente e só continue se não houver parede à frente
            if (cima) {
                if (alinhado && (posy == 0 || mapa[posy - 1][posx] == '1')) {
                    cima = false;
                } else {
                    float destino = (posy - 1) * tamanho_bloco;     // Destino do pacman (posição acima na grade)
                    if (pacmanY > destino)      // Caso ainda não tenha chegado ao destino, continue movendo
                        pacmanY -= velocidade * deltaTime;
                    if (pacmanY < destino) {        // Se já chegou ao destino, ajuste a posição
                        pacmanY = destino;
                        posy--;
                    }
                }
            }
            else if (baixo) {
                if (alinhado && (posy == 29 || mapa[posy + 1][posx] == '1')) {
                    baixo = false;
                } else {
                    float destino = (posy + 1) * tamanho_bloco;     // Destino do pacman (posição abaixo na grade)
                    if (pacmanY < destino)      // Caso ainda não tenha chegado ao destino, continue movendo
                        pacmanY += velocidade * deltaTime;
                    if (pacmanY > destino) {        // Se já chegou ao destino, ajuste a posição
                        pacmanY = destino;
                        posy++;
                    }
                }
            }
            else if (esq) {
                if (alinhado && !((posx > 0 && mapa[posy][posx - 1] != '1') || (posx == 0 && posy == LINHA_DO_TUNEL))) {
                    esq = false;
                } else {
                    float destino = (posx - 1) * tamanho_bloco;     // Destino do pacman (posição à esquerda na grade)
                    if (pacmanX > destino)      // Caso ainda não tenha chegado ao destino, continue movendo
                        pacmanX -= velocidade * deltaTime;
                    if (pacmanX < destino) {        // Se já chegou ao destino, ajuste a posição    
                        pacmanX = destino;
                        posx--;
                    }
                }
            }
            else if (dir) {
                if (alinhado && !((posx < 27 && mapa[posy][posx + 1] != '1') || (posx == 27 && posy == LINHA_DO_TUNEL))) {
                    dir = false;
                } else {
                    float destino = (posx + 1) * tamanho_bloco;     // Destino do pacman (posição à direita na grade)
                    if (pacmanX < destino)      // Caso ainda não tenha chegado ao destino, continue movendo
                        pacmanX += velocidade * deltaTime;
                    if (pacmanX > destino) {        // Se já chegou ao destino, ajuste a posição
                        pacmanX = destino;
                        posx++;
                    }
                }
            }

			// Pontuacao e coleta de itens
			if (mapa[posy][posx] == '0') {  // Se comer comida
                mapa[posy][posx] = ' ';
				score += 10;    // Pontos da comida
                scoreText.setString("Score: " + to_string(score));
            }
			else if (mapa[posy][posx] == '3') {     // Se comer poder
                mapa[posy][posx] = ' ';
				score += 50;    // Pontos do poder
                scoreText.setString("Score: " + to_string(score));
            }
            else if (mapa[posy][posx] == '4') { // Se comer banana
                mapa[posy][posx] = ' ';
                score += 100; // Pontos da banana
                scoreText.setString("Score: " + to_string(score));
            }
            else if (mapa[posy][posx] == '5') { // Se comer morango
                mapa[posy][posx] = ' ';
                score += 100; // Pontos do morango
                scoreText.setString("Score: " + to_string(score));
            }
            else if (mapa[posy][posx] == '6') { // Se comer cereja
                mapa[posy][posx] = ' ';
                score += 100; // Pontos da cereja
                scoreText.setString("Score: " + std::to_string(score));
            }

            // Atualiza a posição do fantasma
            
        }

        // Linha do tunel (Travessia de uma extremidade a outra)
        const int LINHA_DO_TUNEL = 14;
        if (posy == LINHA_DO_TUNEL) {
            // Indo para a direita, saiu do limite direito
            if (posx > 27) {
                float destino = 0 * tamanho_bloco;
                if (pacmanX < destino) {
                    pacmanX += velocidade * deltaTime;
                    if (pacmanX > destino) pacmanX = destino;
                } else {
                    pacmanX = destino;
                    posx = 0;
                }
            }
            // Indo para a esquerda, saiu do limite esquerdo
            else if (posx < 0) {
                float destino = 27 * tamanho_bloco;
                if (pacmanX > destino) {
                    pacmanX -= velocidade * deltaTime;
                    if (pacmanX < destino) pacmanX = destino;
                } else {
                    pacmanX = destino;
                    posx = 27;
                }
            }
        }

		// Limpar a janela e desenhar os elementos
        window.clear(sf::Color::Black);

		// Desenhar as paredes do mapa
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 28; j++) {
                if (mapa[i][j] == '1') {
                    rectangle.setPosition(j * tamanho_bloco, i * tamanho_bloco);
                    window.draw(rectangle);
                }
            }
        }

		//Desenhar os itens no mapa(comida, poder, banana, morango, cereja)
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 28; j++) {
                if (mapa[i][j] == '0') { // Comida
                    comida.setPosition(j * tamanho_bloco + centralizar_comida, i * tamanho_bloco + centralizar_comida);
                    window.draw(comida);
                }
                else if (mapa[i][j] == '3') { // Poder
                    poder.setPosition(j * tamanho_bloco + centralizar_poder, i * tamanho_bloco + centralizar_poder);
                    window.draw(poder);
                }
                else if (mapa[i][j] == '4') { // Banana
                    spritebanana.setPosition(j * tamanho_bloco + centralizar, i * tamanho_bloco + centralizar);
                    window.draw(spritebanana);
                }
                else if (mapa[i][j] == '5') { // Morango
                    spritemorango.setPosition(j * tamanho_bloco + centralizar, i * tamanho_bloco + centralizar);
                    window.draw(spritemorango);
                }
                else if (mapa[i][j] == '6') { // Cereja
                    spritecereja.setPosition(j * tamanho_bloco + centralizar, i * tamanho_bloco + centralizar);
                    window.draw(spritecereja);
                }
            }
        }

		// Regula posicao do pacman e desenha o sprite correspondente
        if (olhadireita) {
            spriteDir.setPosition(pacmanX + centralizar, pacmanY + centralizar);
            window.draw(spriteDir);
        }
        else if (olhaesquerda) {
            spriteEsq.setPosition(pacmanX + centralizar, pacmanY + centralizar);
            window.draw(spriteEsq);
        }
        else if (olhacima) {
            spriteCima.setPosition(pacmanX + centralizar, pacmanY + centralizar);
            window.draw(spriteCima);
        }
        else if (olhabaixo) {
            spriteBaixo.setPosition(pacmanX + centralizar, pacmanY + centralizar);
            window.draw(spriteBaixo);
        }

		// Desenhar as vidas restantes
        for (int i = 0; i < vidas; ++i) {
            spriteDir.setPosition((i * (tamanho_bloco + 5)) + 10, 30 * tamanho_bloco + 10);
            window.draw(spriteDir);
        }

        fantasmaVermelho.posX += ((fantasmaVermelho.blocoX * tamanho_bloco) - fantasmaVermelho.posX) * 0.2f;
        fantasmaVermelho.posY += ((fantasmaVermelho.blocoY * tamanho_bloco) - fantasmaVermelho.posY) * 0.2f;
        fantasmaAmarelo.posX += ((fantasmaAmarelo.blocoX * tamanho_bloco) - fantasmaAmarelo.posX) * 0.2f;
        fantasmaAmarelo.posY += ((fantasmaAmarelo.blocoY * tamanho_bloco) - fantasmaAmarelo.posY) * 0.2f;
        fantasmaRosa.posX += ((fantasmaRosa.blocoX * tamanho_bloco) - fantasmaRosa.posX) * 0.2f;
        fantasmaRosa.posY += ((fantasmaRosa.blocoY * tamanho_bloco) - fantasmaRosa.posY) * 0.2f;
        fantasmaAzul.posX += ((fantasmaAzul.blocoX * tamanho_bloco) - fantasmaAzul.posX) * 0.2f;
        fantasmaAzul.posY += ((fantasmaAzul.blocoY * tamanho_bloco) - fantasmaAzul.posY) * 0.2f;
        
        if (ghostClock.getElapsedTime().asSeconds() > ghostDelay) {
            fantasmaVermelho.movimento_aleatorio(mapa);
            fantasmaAmarelo.movimento_aleatorio(mapa);
            fantasmaRosa.movimento_aleatorio(mapa);
            fantasmaAzul.movimento_aleatorio(mapa);
            
            fantasmaVermelho.mover(mapa);
            fantasmaAmarelo.mover(mapa);
            fantasmaRosa.mover(mapa);
            fantasmaAzul.mover(mapa);
            ghostClock.restart();
        }
        
        fantasmaVermelho.desenhar(window, tamanho_bloco, centralizar);
        fantasmaAmarelo.desenhar(window, tamanho_bloco, centralizar);
        fantasmaRosa.desenhar(window, tamanho_bloco, centralizar);
        fantasmaAzul.desenhar(window, tamanho_bloco, centralizar);
		// Desenhar o texto de pontuacao
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
