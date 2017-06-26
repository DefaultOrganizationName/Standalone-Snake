# Змейка
## Описание и правила:
  Самая обычная змейка со следующими правилами:
  * Столкновение с краем поля -- проигрыш
  * Столкновение с хвостом змейки -- проигрыш
  * При каждом съедании змейка увеличивается в длину на 1 символ
## Управление:
  * Ну типа кнопка кнопка и херак что-то случилось
## Цели и текущее состояние проекта:
  - [X] Сделать загрузочную флешку и написать свои функции ввода-вывода. В роли загрузчика использовать grub.
  - [X] Написать основные функции игры
     - [X] Инициализация поля и отрисовка границ
     - [X] Инициализация змейки с начальными размерами
     - [X] Рандомное расположение яблок
     - [X] Написать управление клавишами (get_key_pressed из standalone_snake_game.c)
     - [ ] Добавить вывод очков
  - [ ] Добавить основное меню и возможность рестарта
  - [ ] Добавить список игроков, их позиции и результаты
      * Результаты будут храниться в отдельном файле и выводиться в начале и конце игры
