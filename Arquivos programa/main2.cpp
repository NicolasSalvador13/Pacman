#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

char mapa[30][29] = {
	// mapa do Pac
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
int posx = 4, posy = 5;
bool cima = false, baixo = false, esq = false, dir = false;

bool olhadireita = true;
bool olhaesquerda = false;
bool olhacima = false;
bool olhabaixo = false;

int main() {
    int vidas = 3;
    int score = 0;
    float tamanho_bloco = 28;
    float fator_pacman = 0.85f;
    float raio_comida = 3.f;
    float raio_poder = 8.f;
    float offset_comida = (tamanho_bloco / 2.0f) - raio_comida;
    float offset_poder = (tamanho_bloco / 2.0f) - raio_poder;

    float tamanho_pacman_real = tamanho_bloco * fator_pacman;
    float offset = (tamanho_bloco - tamanho_pacman_real) / 2.0f;

    int largura_janela_total = tamanho_bloco * 28;
    int altura_janela_total = tamanho_bloco * 30 + 80;

    sf::RenderWindow window(sf::VideoMode(largura_janela_total, altura_janela_total), "Pac-Man");
    window.setFramerateLimit(60);

    sf::RectangleShape rectangle(sf::Vector2f(tamanho_bloco, tamanho_bloco));
    rectangle.setFillColor(sf::Color(0, 35, 102));

    sf::CircleShape comida(raio_comida);
    comida.setFillColor(sf::Color(204, 169, 221));

    sf::CircleShape poder(raio_poder);
    poder.setFillColor(sf::Color::White);

    sf::Font font;
    if (!font.loadFromFile("Oxanium-ExtraBold.ttf")) {
        cout << "Erro: Nao foi possivel carregar a fonte!" << endl;
        return 1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: 0");
    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    float centerX = largura_janela_total / 2.0f;
    float centerY = 20.0f;
    scoreText.setPosition(centerX - 5, centerY - 5);

    // <-- CORREÇÃO 1: Carregar Pac-Man ANTES das frutas
    //pac man direita
    sf::Texture textureDir;
    if (!textureDir.loadFromFile("pacman.png")) { return 1; }
    sf::Sprite spriteDir;
    spriteDir.setTexture(textureDir);
    spriteDir.setScale(tamanho_pacman_real / textureDir.getSize().x, tamanho_pacman_real / textureDir.getSize().y);

    //Tamanho banana
    sf::Texture texturebanana;
    if (!texturebanana.loadFromFile("banana.png")) { return 1; }
    sf::Sprite spritebanana;
    spritebanana.setTexture(texturebanana);
    // <-- CORREÇÃO 2: Usar a própria textura da banana para o cálculo
    spritebanana.setScale(tamanho_pacman_real / texturebanana.getSize().x, tamanho_pacman_real / texturebanana.getSize().y);

    //Tamanho morango
    sf::Texture texturemorango;
    if (!texturemorango.loadFromFile("morango.png")) { return 1; }
    sf::Sprite spritemorango;
    spritemorango.setTexture(texturemorango);
    // <-- CORREÇÃO 2: Usar a própria textura do morango para o cálculo
    spritemorango.setScale(tamanho_pacman_real / texturemorango.getSize().x, tamanho_pacman_real / texturemorango.getSize().y);

    //Tamanho cereja
    sf::Texture texturecereja;
    if (!texturecereja.loadFromFile("cereja.png")) { return 1; }
    sf::Sprite spritecereja;
    spritecereja.setTexture(texturecereja);
    // <-- CORREÇÃO 2: Usar a própria textura da cereja para o cálculo
    spritecereja.setScale(tamanho_pacman_real / texturecereja.getSize().x, tamanho_pacman_real / texturecereja.getSize().y);

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

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    esq = true; dir = cima = baixo = false;
                    olhaesquerda = true; olhadireita = olhacima = olhabaixo = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    dir = true; esq = cima = baixo = false;
                    olhadireita = true; olhaesquerda = olhacima = olhabaixo = false;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    cima = true; esq = dir = baixo = false;
                    olhacima = true; olhadireita = olhaesquerda = olhabaixo = false;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    baixo = true; esq = dir = cima = false;
                    olhabaixo = true; olhadireita = olhaesquerda = olhacima = false;
                }
            }
        }

        if (clock.getElapsedTime() > sf::seconds(0.2)) {
            clock.restart();
            const int LINHA_DO_TUNEL = 14;

            if (cima && posy > 0 && mapa[posy - 1][posx] != '1')
                posy--;

            if (baixo && posy < 29 && mapa[posy + 1][posx] != '1')
                posy++;

            if (esq) {
                if ((posx > 0 && mapa[posy][posx - 1] != '1') || (posx == 0 && posy == LINHA_DO_TUNEL)) {
                    posx--;
                }
            }
            if (dir) {
                if ((posx < 27 && mapa[posy][posx + 1] != '1') || (posx == 27 && posy == LINHA_DO_TUNEL)) {
                    posx++;
                }
            }

            // <-- CORREÇÃO 4: Adicionar lógica para comer as frutas
            if (mapa[posy][posx] == '0') {
                mapa[posy][posx] = ' ';
                score += 10;
                scoreText.setString("Score: " + std::to_string(score));
            }
            else if (mapa[posy][posx] == '3') {
                mapa[posy][posx] = ' ';
                score += 50;
                scoreText.setString("Score: " + std::to_string(score));
            }
            else if (mapa[posy][posx] == '4') { // Se comer banana
                mapa[posy][posx] = ' ';
                score += 100; // Pontos da banana
                scoreText.setString("Score: " + std::to_string(score));
            }
            else if (mapa[posy][posx] == '5') { // Se comer morango
                mapa[posy][posx] = ' ';
                score += 100; // Pontos do morango
                scoreText.setString("Score: " + std::to_string(score));
            }
            else if (mapa[posy][posx] == '6') { // Se comer cereja
                mapa[posy][posx] = ' ';
                score += 100; // Pontos da cereja
                scoreText.setString("Score: " + std::to_string(score));
            }
        }

        const int LINHA_DO_TUNEL = 14;
        if (posx > 27 && posy == LINHA_DO_TUNEL) {
            posx = 0;
        }
        else if (posx < 0 && posy == LINHA_DO_TUNEL) {
            posx = 27;
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 28; j++) {
                if (mapa[i][j] == '1') {
                    rectangle.setPosition(j * tamanho_bloco, i * tamanho_bloco);
                    window.draw(rectangle);
                }
            }
        }

		//Dedenhar os itens no mapa(comida, poder, banana, morango, cereja)
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 28; j++) {
                if (mapa[i][j] == '0') { // Comida
                    comida.setPosition(j * tamanho_bloco + offset_comida, i * tamanho_bloco + offset_comida);
                    window.draw(comida);
                }
                else if (mapa[i][j] == '3') { // Poder
                    poder.setPosition(j * tamanho_bloco + offset_poder, i * tamanho_bloco + offset_poder);
                    window.draw(poder);
                }
                else if (mapa[i][j] == '4') { // Banana
                    spritebanana.setPosition(j * tamanho_bloco + offset, i * tamanho_bloco + offset);
                    window.draw(spritebanana);
                }
                else if (mapa[i][j] == '5') { // Morango
                    spritemorango.setPosition(j * tamanho_bloco + offset, i * tamanho_bloco + offset);
                    window.draw(spritemorango);
                }
                else if (mapa[i][j] == '6') { // Cereja
                    spritecereja.setPosition(j * tamanho_bloco + offset, i * tamanho_bloco + offset);
                    window.draw(spritecereja);
                }
            }
        }

        if (olhadireita) {
            spriteDir.setPosition(posx * tamanho_bloco + offset, posy * tamanho_bloco + offset);
            window.draw(spriteDir);
        }
        else if (olhaesquerda) {
            spriteEsq.setPosition(posx * tamanho_bloco + offset, posy * tamanho_bloco + offset);
            window.draw(spriteEsq);
        }
        else if (olhacima) {
            spriteCima.setPosition(posx * tamanho_bloco + offset, posy * tamanho_bloco + offset);
            window.draw(spriteCima);
        }
        else if (olhabaixo) {
            spriteBaixo.setPosition(posx * tamanho_bloco + offset, posy * tamanho_bloco + offset);
            window.draw(spriteBaixo);
        }

        for (int i = 0; i < vidas; ++i) {
            spriteDir.setPosition((i * (tamanho_bloco + 5)) + 10, 30 * tamanho_bloco + 10);
            window.draw(spriteDir);
        }

        window.draw(scoreText);
        window.display();
    }

    return 0;
}