#define main project_main
#include "../Solution/main.cpp"
#undef main

#include <cassert>

void assertMatch(const Match &match, int start, int end)
{
    assert(match.start == start);
    assert(match.end == end);
}

int main()
{
    Match matches[] = {
        {5, 8},
        {1, 3},
        {5, 10},
        {2, 7},
        {1, 9},
        {5, 5},
        {9, 12},
        {2, 4}};

    int count = sizeof(matches) / sizeof(matches[0]);

    sortMatches(matches, count);

    assertMatch(matches[0], 1, 9);
    assertMatch(matches[1], 1, 3);
    assertMatch(matches[2], 2, 7);
    assertMatch(matches[3], 2, 4);
    assertMatch(matches[4], 5, 10);
    assertMatch(matches[5], 5, 8);
    assertMatch(matches[6], 5, 5);
    assertMatch(matches[7], 9, 12);

    Match single[] = {{3, 6}};
    sortMatches(single, 1);
    assertMatch(single[0], 3, 6);

    sortMatches(nullptr, 0);

    return 0;
}
