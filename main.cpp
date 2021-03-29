//#include <SFML/Graphics.hpp>
//#include <ctime>
//using namespace sf;
//
//const int M = 30; // высота игрового поля
//const int N = 15; // ширина игрового поля
//
//int field[M][N] = { 0 }; // игровое поле
//
//// Массив фигурок-тетрамино
//int figures[7][4] =
//        {
//                1,3,5,7, // I
//                2,4,5,7, // Z
//                3,5,4,6, // S
//                3,5,4,7, // T
//                2,3,5,7, // L
//                3,5,7,6, // J
//                2,3,4,5, // O
//        };
//
//struct Point
//{
//    int x, y;
//} a[4], b[4];
//
//// Проверка на выход за границы игрового поля
//bool check()
//{
//    for (int i = 0; i < 4; i++)
//        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
//        else if (field[a[i].y][a[i].x]) return 0;
//
//    return 1;
//
//};
//
//
//int main()
//{
//    srand(time(0));
//
//    RenderWindow window(VideoMode(771, 675), "The Game!");
//
//    // Создание и загрузка текстуры
//    Texture texture, texture_background, texture_frame;
//    texture.loadFromFile("img/titles.png");
//    texture_background.loadFromFile("img/TypeA300.png");
//    texture_frame.loadFromFile("");
//
//    // Создание спрайта
//    Sprite sprite(texture), sprite_background(texture_background), sprite_frame(texture_frame);
//
//    // Вырезаем из спрайта отдельный квадратик размером 18х18 пикселей
//    sprite.setTextureRect(IntRect(0, 0, 16, 16));
//
//    // Переменные для горизонтального перемещения и вращения
//    int dx = 0; bool rotate = 0; int colorNum = 1; bool beginGame = true; int n = rand() % 7;
//
//    // Переменные для таймера и задержки
//    float timer = 0, delay = 0.3;
//
//    // Часы (таймер)
//    Clock clock;
//
//
//    // Главный цикл приложения. Выполняется, пока открыто окно
//    while (window.isOpen())
//    {
//        // Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
//        float time = clock.getElapsedTime().asSeconds();
//        clock.restart();
//        timer += time;
//
//        // Обрабатываем очередь событий в цикле
//        Event event;
//        while (window.pollEvent(event))
//        {
//            // Пользователь нажал на «крестик» и хочет окно закрыть?
//            if (event.type == Event::Closed)
//                // тогда закрываем его
//                window.close();
//
//            // Была нажата кнопка на клавиатуре?
//            if (event.type == Event::KeyPressed)
//                // Эта кнопка – стрелка вверх?…
//                if (event.key.code == Keyboard::Up) rotate = true;
//                    // …или же стрелка влево?…
//                else if (event.key.code == Keyboard::Left) dx = -1;
//                    // …ну тогда может это стрелка вправо?
//                else if (event.key.code == Keyboard::Right) dx = 1;
//        }
//
//        // Нажали кнопку "вниз"? Ускоряем падение тетрамино
//        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
//
//        //// Горизонтальное перемещение ////
//        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
//
//        // Вышли за пределы поля после перемещения? Тогда возвращаем старые координаты
//        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

//
//        //// Вращение ////
//        if (rotate)
//        {
//            Point p = a[1]; // задаем центр вращения
//            for (int i = 0; i < 4; i++)
//            {
//                int x = a[i].y - p.y; //y-y0
//                int y = a[i].x - p.x; //x-x0
//                a[i].x = p.x - x;
//                a[i].y = p.y + y;
//            }
//            // Вышли за пределы поля после поворота? Тогда возвращаем старые координаты
//            if (!check()) { for (int i = 0; i < 4; i++) a[i] = b[i]; }
//
//        }
//
//        //// Движение тетрамино вниз (Тик таймера) ////
//        if (timer > delay)
//        {
//            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
//            if (!check())
//            {
//                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
//                colorNum = 1 + rand() % 7;
//                n = rand() % 7;
//                for (int i = 0; i < 4; i++)
//                {
//                    a[i].x = figures[n][i] % 2;
//                    a[i].y = figures[n][i] / 2;
//                }
//
//            }
//            timer = 0;
//
//        }
//
//        //----ПРОВЕРКА ЛИНИИ----//
//        int k = M - 1;
//        for (int i = M - 1; i > 0; i--)
//        {
//            int count = 0;
//            for (int j = 0; j < N; j++)
//            {
//                if (field[i][j]) count++;
//                field[k][j] = field[i][j];
//            }
//            if (count < N) k--;
//        }
//
//        // Первое появление тетрамино на поле?
//        if (beginGame)
//        {
//            beginGame = false;
//            n = rand() % 7;
//            for (int i = 0; i < 4; i++)
//            {
//                a[i].x = figures[n][i] % 2;
//                a[i].y = figures[n][i] / 2;
//            }
//        }
//        dx = 0; rotate = 0; delay = 0.3;
//
//        //----ОТРИСОВКА----//
//
//        // Задаем цвет фона - белый
//        window.clear(Color::White);
//        window.draw(sprite_background);
//        for (int i = 0; i < M; i++)
//            for (int j = 0; j < N; j++)
//            {
//                if (field[i][j] == 0) continue;
//                sprite.setTextureRect(IntRect(8, 0, 8, 8));
//                sprite.setPosition(j * 16, i * 16);
//                sprite.setScale(2, 2);
//                sprite.move(288, 120); // смещение
//                window.draw(sprite);
//            }
//
//        for (int i = 0; i < 4; i++)
//        {
//            // Разукрашиваем тетрамино
//            sprite.setTextureRect(IntRect(8, 0, 8, 8));
//
//            // Устанавливаем позицию каждого кусочка тетрамино
//            sprite.setPosition(a[i].x * 16, a[i].y * 16);
//            sprite.setScale(2, 2);
//
//            sprite.move(288, 120); // смещение
//
//            // Отрисовка спрайта
//            window.draw(sprite);
//        }
//        // Отрисовка фрейма
//        window.draw(sprite_frame);
//
//        // Отрисовка окна
//        window.display();
//    }
//
//    return 0;
//}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include <iostream>
#include <random>

const int TETRA_SIZE = 16;
const int M = 30; // height
const int N = 15; // width
const int MAP_LEFT_EDGE = 288; // px
const int MAP_UP_EDGE = 120; // px
const int TEXT_OFFSET = 272; // px
const int LINE_SCORE = 1000;

int map[M][N] = {0};

int tetraminos[7][4] = {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z
        3, 5, 4, 6, // S
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // O
};

struct Point {
    int x;
    int y;
    Point(): x(0), y(0) {};
};

bool check_edge(Point a[]) {
    for (int i = 0; i < 4; ++i) {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)  { // map[a[i].x][a[i].y]
            // std::cout << "false" << '\n';
            return false;
        }
        else if (map[a[i].y][a[i].x]) {
            // std::cout << "a[i].x = " << a[i].x << " a[i].y = " << a[i].y << '\n';
            // std::cout << "map[a.x][a.y] = " << map[a[i].y][a[i].x] << '\n';
            return false;
        }
    }
    //std::cout << "true" << '\n';
    return true;
}

int main() {
    Point a[4];
    Point b[4];
    int dx = 0;
    int dy = 0;
    int color = 0;
    static int top_score = 10000;
    int score = 0;
    int lines_counter = 0;
    int base_char_size = 12;
    float timer = 0;
    float delay = 0.3f;
    float duration = float();
    double multiplier = 0.2;
    bool rotate = false;
    bool is_new = true;
    sf::Event event{};
    int tetramino_counter[7] = { 0 };

    sf::RenderWindow window(sf::VideoMode(771, 675), "Tetris");
    window.setFramerateLimit(60);

    sf::Clock clock{};
    sf::Clock rotate_timer{};
    sf::Clock flash_clock{};

    sf::Font tetris_font;
    tetris_font.loadFromFile("fonts/tetris-block-regular.ttf");

    sf::Texture main_theme_txt; // 526 x 460 or 771 x 675 10 x 20 tetraminos
    main_theme_txt.loadFromFile("img/TypeA300.png");
    main_theme_txt.setSmooth(true);

    sf::Texture tetramino_txt;
    tetramino_txt.loadFromFile("img/titles.png");

    sf::Music m_theme_mus;
    m_theme_mus.openFromFile("snd/tetris-gameboy-02.wav");

    sf::Sprite main_theme_spr(main_theme_txt);
    sf::Sprite cube_sprite(tetramino_txt);
    cube_sprite.setTextureRect(sf::IntRect(16, 8 * color, 8, 8));
    cube_sprite.setScale(2, 2);
//    cube_sprite.setTexture(tetramino_txt);
//    cube_sprite.setTextureRect(sf::IntRect(16, 0, 8, 8));
//    cube_sprite.setScale(2, 2);

    //main_theme_spr.setTexture(main_theme_txt);
    //m_theme_mus.play();
    // 16*18 <-> 16*32 ; 16*7.5 <-> 16*38.5
    //blue_tetra_spr.setPosition(TETRA_SIZE * 18, TETRA_SIZE * 7.5); // left_start: 288, top_start: 120, right_end: 512, bottom_end: 592;
    //cube_sprite.setPosition(TETRA_SIZE * 18, TETRA_SIZE * 37); // x_size: 224, x_tetr: 16, y_size: 472, y_tetr: 29,5;
    //blue_tetra_spr.setOrigin(TETRA_SIZE * 10, TETRA_SIZE * 10);
    //main_theme_spr.setTextureRect(sf::IntRect(50, 50, 100, 100));

    while (window.isOpen()) {
        sf::Time dt = flash_clock.restart();
        duration += dt.asSeconds();

        float time = rotate_timer.getElapsedTime().asSeconds();
        rotate_timer.restart();
        timer += time;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    rotate = true;
                else if (event.key.code == sf::Keyboard::Left)
                    dx = -1;
                else if (event.key.code == sf::Keyboard::Right)
                    dx = 1;
            }
        }
        // + delay
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            delay = 0.05;

        // movement
        for (int i = 0; i < 4; ++i) {
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check_edge(a)) {
            for (int i = 0; i < 4; ++i)
                a[i] = b[i];
        }

        if (rotate) {
            Point p = a[1];
            for (auto & i : a) {
                int x = i.y - p.y;
                int y = i.x - p.x;
                i.x = p.x - x;
                i.y = p.y + y;
            }
            if (!check_edge(a)) {
                for (int i = 0; i < 4; ++i)
                    a[i] = b[i];
            }
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> type_dist(0, 6);
        std::uniform_int_distribution<int> color_dist(0, 6);
        int n = type_dist(mt);
        //++tetramino_counter[n];

        if (timer > delay) {
            //++tetramino_counter[n];
            for (int i = 0; i < 4; ++i) {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check_edge(a)) {
                ++tetramino_counter[n];
                for (auto & i : b)
                    map[i.y][i.x] = color;
                color = color_dist(mt);
                for (int i = 0; i < 4; ++i) {
                    a[i].x = tetraminos[n][i] % 2;
                    a[i].y = tetraminos[n][i] / 2;
                }
            }
            timer = 0;
        }

        // check line
        int k = M - 1;
        int lines_in_row_counter = 0;
        for (int i = k; i > 0; --i) {
            int count = 0;
            for (int j = 0; j < N; ++j) {
                if (map[i][j])
                    ++count;
                map[k][j] = map[i][j];
            }
            if (count < N)
                --k;
            else
                ++lines_in_row_counter;
        }
        // set score
        if (lines_in_row_counter > 1)
            score += (lines_in_row_counter + (multiplier * lines_in_row_counter)) * LINE_SCORE;
        else if (lines_in_row_counter == 1)
            score += LINE_SCORE;
        lines_counter += lines_in_row_counter;
        //std::cout << multiplier * lines_in_row_counter << '\n';

        // first tetramino
        if (is_new) {
            is_new = false;
            n = type_dist(mt);
            ++tetramino_counter[n];
            for (int i = 0; i < 4; ++i) {
                a[i].x = tetraminos[n][i] % 2;
                a[i].y = tetraminos[n][i] / 2;
            }
        }
        dx = 0;
        rotate = false;
        delay = 0.3;

        sf::Time cur_time = clock.getElapsedTime();
        std::string str_time = std::to_string(cur_time.asSeconds());
        //std::cout << str_time << '\n';

        sf::Text time_text;
        time_text.setString(str_time);
        time_text.setFont(tetris_font);
        time_text.setFillColor(sf::Color::White);
        time_text.setStyle(sf::Text::Style::Regular);
        time_text.setCharacterSize(13);
        time_text.setPosition(TETRA_SIZE * 36.4, TETRA_SIZE * 3.5);

        sf::Text score_text;
        //sf::Text stat_text;
        sf::Text top_score_text;
        sf::Text tetra_count_text;
        sf::Text lines_count_text;

        score_text.setString(std::to_string(score));
        score_text.setFont(tetris_font);
        score_text.setFillColor(sf::Color::White);
        score_text.setStyle(sf::Text::Style::Bold);
        score_text.setCharacterSize(14);
        score_text.setLetterSpacing(3);
        score_text.setPosition(TETRA_SIZE * 36.4, TETRA_SIZE * 11);

        top_score_text.setString(std::to_string(top_score));
        top_score_text.setFont(tetris_font);
        top_score_text.setFillColor(sf::Color::White);
        top_score_text.setStyle(sf::Text::Style::Bold);
        top_score_text.setCharacterSize(14);
        top_score_text.setLetterSpacing(3);
        top_score_text.setPosition(TETRA_SIZE * 36.8, TETRA_SIZE * 6.5);

        lines_count_text.setString(std::to_string(lines_counter));
        lines_count_text.setFont(tetris_font);
        lines_count_text.setFillColor(sf::Color::White);
        lines_count_text.setStyle(sf::Text::Style::Bold);
        lines_count_text.setCharacterSize(14);
        lines_count_text.setLetterSpacing(4);
        lines_count_text.setPosition(TETRA_SIZE * 29, TETRA_SIZE * 3.5);

        window.clear(sf::Color(sf::Color::White));
        window.draw(main_theme_spr);

        //
        gui::Button start("Start", tetris_font, sf::Vector2f(100.f, 50.f), gui::style::clean);
        //start.setPosition(500.f, 500.f);

        //

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (map[i][j] == 0)
                    continue;
                cube_sprite.setTextureRect(sf::IntRect(16, 8 * color, 8, 8));
                cube_sprite.setScale(2, 2);
                cube_sprite.setPosition(TETRA_SIZE * j, TETRA_SIZE * i);
                cube_sprite.move(MAP_LEFT_EDGE, MAP_UP_EDGE);
                window.draw(cube_sprite);
            }
        }

        for (auto & i : a) {
            cube_sprite.setTextureRect(sf::IntRect(16, 8 * color, 8, 8));
            cube_sprite.setScale(2, 2);
            cube_sprite.setPosition(TETRA_SIZE * i.x, TETRA_SIZE * i.y);
            cube_sprite.move(MAP_LEFT_EDGE, MAP_UP_EDGE);
            window.draw(cube_sprite);
        }

        window.draw(score_text);
        window.draw(top_score_text);
        window.draw(lines_count_text);

        // draw text statistics
        for (int i = 0; i < 7; ++i) {
            sf::Text stat_text{};
            stat_text.setString(std::to_string(tetramino_counter[i]));
            stat_text.setFont(tetris_font);
            stat_text.setFillColor(sf::Color::White);
            stat_text.setStyle(sf::Text::Style::Regular);
            stat_text.setCharacterSize(14);
            if (i == 0) {
                stat_text.setPosition(TETRA_SIZE * 11, (TETRA_SIZE) + TEXT_OFFSET);
            } else if (i > 0) {
                stat_text.setPosition(TETRA_SIZE * 11, (TETRA_SIZE) + TEXT_OFFSET);
                //stat_text.move(0, TETRA_SIZE);
            }

            window.draw(stat_text);
        }

        window.draw(time_text);

        // game over check
        for (int i = 0; i < N; ++i) {
            if (map[1][i]) {
                window.clear(sf::Color(sf::Color::Black));
                sf::Text endgame_text;
                endgame_text.setString("Game over! Press Enter to close the window!");
                endgame_text.setFont(tetris_font);
                endgame_text.setCharacterSize(14);
                endgame_text.setFillColor(sf::Color::White);
                endgame_text.setStyle(sf::Text::Style::Regular);
                endgame_text.setPosition(50, window.getSize().y / 2);

                if (duration > 0.01f) {
                    duration = 0;
                    if (base_char_size < 15) {
                        ++base_char_size;
                    } else if (base_char_size > 15) {
                        --base_char_size;
                        while (base_char_size != 12) {
                            endgame_text.setCharacterSize(base_char_size);
                            window.draw(endgame_text);
                            --base_char_size;
                        }
                    }
                    endgame_text.setCharacterSize(base_char_size);
                }
                window.draw(endgame_text);

                while (window.pollEvent(event)) {
                    window.draw(endgame_text);
                    while (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Enter)
                            window.close();
                    }
                    if (event.type == sf::Event::KeyPressed)
                        if (event.key.code == sf::Keyboard::Enter)
                            window.close();
                }
            }
        }

        start.update(event, window);
        window.draw(start);
        window.display();
    }

    return 0;
}
// deprecated
//txt_size = main_theme_txt.getSize();
//win_size = window.getSize();
//
//float scale_x = (float) win_size.x / txt_size.x;
//float scale_y = (float) win_size.y / txt_size.y;
//
//std::cout << "tX: " << txt_size.x << " tY: " << txt_size.y <<
//" wX: " << win_size.x << " wY: " << win_size.y << " scaleX: " << scale_x << " scaleY: " << scale_y << '\n';
//
//earth_spr.setTexture(main_theme_txt);
//earth_spr.setScale(scale_x, scale_y);
