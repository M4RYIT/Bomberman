#include "clove.h"
#include "bomberman.h"

CLOVE_TEST(Movable_FixPositionX)
{
    level lv;
    int32_t map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 8, map);

    movable mv = {1, 0, 4, 4};
    move_on_level(&lv, &mv, -10, 0);
    CLOVE_FLOAT_EQ(0, mv.x);
}

CLOVE_TEST(Movable_FixPositionWidth)
{
    level lv;
    int32_t map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 8, map);

    movable mv = {1, 0, 4, 4};
    move_on_level(&lv, &mv, 30, 0);
    CLOVE_FLOAT_EQ(20, mv.x);
}

CLOVE_TEST(Movable_FixPositionY)
{
    level lv;
    int32_t map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 8, map);

    movable mv = {1, 0, 4, 4};
    move_on_level(&lv, &mv, 0, -10);
    CLOVE_FLOAT_EQ(0, mv.y);
}

CLOVE_TEST(Movable_FixPositionHeight)
{
    level lv;
    int32_t map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 8, map);

    movable mv = {1, 0, 4, 4};
    move_on_level(&lv, &mv, 0, 30);
    CLOVE_FLOAT_EQ(20, mv.y);
}

CLOVE_TEST(Movable_WallHitRight)
{
    level lv;
    int32_t map[] = {0, 1, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 64, map);

    movable mv = {1, 1, 32, 32};
    move_on_level(&lv, &mv, 50, 0);
    CLOVE_FLOAT_EQ(32, mv.x);
}

CLOVE_TEST(Movable_WallHitLeft)
{
    level lv;
    int32_t map[] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 64, map);

    movable mv = {80, 1, 32, 32};
    move_on_level(&lv, &mv, -30, 0);
    CLOVE_FLOAT_EQ(64, mv.x);
}

CLOVE_TEST(Movable_WallHitUp)
{
    level lv;
    int32_t map[] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 64, map);

    movable mv = {1, 80, 32, 32};
    move_on_level(&lv, &mv, 0, -30);
    CLOVE_FLOAT_EQ(64, mv.y);
}

CLOVE_TEST(Movable_WallHitDown)
{
    level lv;
    int32_t map[] = {0, 0, 0, 1, 0, 0, 0, 0, 0};
    level_init(&lv, 3, 3, 64, map);

    movable mv = {1, 1, 32, 32};
    move_on_level(&lv, &mv, 0, 50);
    CLOVE_FLOAT_EQ(32, mv.y);
}

CLOVE_SUITE(MovableSuite)
{
    CLOVE_SUITE_TESTS(Movable_FixPositionX, Movable_FixPositionWidth, Movable_FixPositionY, Movable_FixPositionHeight,
                      Movable_WallHitRight, Movable_WallHitUp, Movable_WallHitDown);
}