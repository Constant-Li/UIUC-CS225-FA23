#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "Animation.h"
#include "FloodFilledImage.h"
#include "ImageTraversal.h"

#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    bool student_wrote_test_case = true;

    REQUIRE( student_wrote_test_case );

    PNG png;      png.readFromFile("../data/pacman.png");
    PNG expected; expected.readFromFile("../data/pacman-solid-bfs.png");
    PNG expected2; expected2.readFromFile("../data/pacman-solid-bfs-2.png");
    
    FloodFilledImage image(png);
    Traversals::ImageTraversal bfs(png, Point(100, 50), 0.2, {
        Traversals::bfs_add, Traversals::bfs_pop, Traversals::bfs_peek
    });

    HSLAPixel color(231, 1, 0.5);
    MyColorPicker my;
    image.addFloodFill( bfs, my );

    Animation animation = image.animate(1000);

    REQUIRE( animation.frameCount() > 2 );
    PNG secondFrame = animation.getFrame(1);
    PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

    secondFrame.writeToFile("pacman-my-bfs-2.png");
    lastFrame.writeToFile("pacman-my-bfs.png");
    animation.write("pacman-my-bfs.gif");
    INFO("Files written to pacman-my-bfs-* for debugging.");


}
