#include "clove.h"
#include "bomberman.h"

CLOVE_TEST(LevelInit_Null)
{
    CLOVE_INT_EQ(level_init(NULL, 0, 0, 0, NULL), -1);
}

CLOVE_TEST(LevelInit_ZeroCols)
{
    level lv;
    CLOVE_INT_EQ(level_init(&lv, 0, 100, 100, NULL), -1);
}

CLOVE_TEST(LevelInit_ZeroRows)
{
    level lv;
    CLOVE_INT_EQ(level_init(&lv, 100, 0, 100, NULL), -1);
}

CLOVE_TEST(LevelInit_ZeroSize)
{
    level lv;
    CLOVE_INT_EQ(level_init(&lv, 0, 0, 100, NULL), -1);
}

CLOVE_TEST(LevelInit_NullCells)
{
    level lv;
    CLOVE_INT_EQ(level_init(&lv, 100, 100, 100, NULL), 0);
}

CLOVE_TEST(LevelCell_NullContent)
{
    level lv;
    level_init(&lv, 2, 2, 1, NULL);
    CLOVE_INT_EQ(-1, level_cell(&lv, 0, 0));
}

CLOVE_TEST(LevelCell_Content)
{
    level lv;
    int32_t map[] = {1, 1, 1, 1};
    level_init(&lv, 2, 2, 1, map);
    CLOVE_INT_EQ(1, level_cell(&lv, 0, 0));
}

CLOVE_TEST(LevelCell_OffBoundsCol)
{
    level lv;
    int32_t map[] = {1, 1, 1, 1};
    level_init(&lv, 2, 2, 1, map);
    CLOVE_INT_EQ(-1, level_cell(&lv, 5, 0));
}

CLOVE_TEST(LevelCell_OffBoundsRow)
{
    level lv;
    int32_t map[] = {1, 1, 1, 1};
    level_init(&lv, 2, 2, 1, map);
    CLOVE_INT_EQ(-1, level_cell(&lv, 0, 5));
}

CLOVE_TEST(LevelCell_OffBounds)
{
    level lv;
    int32_t map[] = {1, 1, 1, 1};
    level_init(&lv, 2, 2, 1, map);
    CLOVE_INT_EQ(-1, level_cell(&lv, 5, 5));
}

CLOVE_SUITE(LevelSuite)
{
    CLOVE_SUITE_TESTS(LevelInit_Null, LevelInit_ZeroCols, LevelInit_ZeroRows, LevelInit_ZeroSize, LevelInit_NullCells,
                      LevelCell_NullContent, LevelCell_Content, LevelCell_OffBoundsCol, LevelCell_OffBoundsRow,
                      LevelCell_OffBounds);
}