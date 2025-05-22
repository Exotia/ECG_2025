//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#ifndef STAR_TOOL_H
#define STAR_TOOL_H

#include "tool_base.h"
#include <sstream>
using std::stringstream;

// A tool that allows to draw stars with configurable points and radius
class star_tool : public tool_base
{
private:
    // Number of points for the star shape
    int num_points;
    
    // Helper method to render the star at a given position with given radii
    void rasterize_star(int center_x, int center_y, int outer_radius, int inner_radius);

public:
    // Constructor
    star_tool(canvas_buffer& canvas);
    
    // Draw a star with center (x0, y0) and (x1, y1) on the radius
    void draw(int x0, int y0, int x1, int y1) override;
    
    // Put debug output into the stream "stream" to be displayed in the main window
    void set_text(std::stringstream& stream) override;
    
    // Increment the number of points for the star
    void increment_points();
    
    // Decrement the number of points for the star
    void decrement_points();
    
    // Get current number of points
    int get_num_points() const;
};

#endif // STAR_TOOL_H
