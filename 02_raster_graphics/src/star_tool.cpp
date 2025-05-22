//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "star_tool.h"
#include <algorithm>
#include <math.h>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Initialize the tool and store a reference of a canvas_buffer
star_tool::star_tool(canvas_buffer& canvas): tool_base(canvas)
{
    // This tool draws stars!
    shape = TS_CIRCLE; // We use circle shape for preview
    
    // Initialize with 5 points as default
    num_points = 5;
}

// Draw a star with center (x0, y0) and (x1, y1) on the radius
void star_tool::draw(int x0, int y0, int x1, int y1)
{
    // Calculate the outer radius
    int outer_radius = static_cast<int>(sqrt(static_cast<double>((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1))));
    
    // Inner radius is typically 40% of the outer radius for a nice star shape
    int inner_radius = static_cast<int>(outer_radius * 0.4);
    
    // Rasterize the star
    rasterize_star(x0, y0, outer_radius, inner_radius);
}

// Helper method to render the star at a given position with given radii
void star_tool::rasterize_star(int center_x, int center_y, int outer_radius, int inner_radius)
{
    if (outer_radius <= 0) return;
    
    // Use Bresenham's line algorithm to draw the star lines
    auto draw_line = [this](int x0, int y0, int x1, int y1) {
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;
        
        while (true) {
            // Check bounds before setting pixel
            if (x0 >= 0 && x0 < canvas.get_width() && y0 >= 0 && y0 < canvas.get_height()) {
                canvas.set_pixel(x0, y0);
            }
            
            if (x0 == x1 && y0 == y1) break;
            
            int e2 = 2 * err;
            if (e2 > -dy) {
                if (x0 == x1) break;
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                if (y0 == y1) break;
                err += dx;
                y0 += sy;
            }
        }
    };
    
    // Calculate the vertices of the star
    // We need 2*num_points vertices (alternating outer and inner points)
    std::vector<std::pair<int, int> > vertices; // C++98 compatible
    
    for (int i = 0; i < 2 * num_points; i++) {
        // Determine the angle for this vertex
        double angle = i * M_PI / num_points;
        
        // Determine the radius for this vertex (outer for even, inner for odd)
        int radius = (i % 2 == 0) ? outer_radius : inner_radius;
        
        // Calculate the vertex position
        int x = center_x + static_cast<int>(radius * sin(angle));
        int y = center_y - static_cast<int>(radius * cos(angle));
        
        vertices.push_back(std::make_pair(x, y));
    }
    
    // Draw lines between consecutive vertices to create the star shape
    for (size_t i = 0; i < vertices.size(); i++) {
        size_t next = (i + 1) % vertices.size();
        draw_line(vertices[i].first, vertices[i].second, 
                 vertices[next].first, vertices[next].second);
    }
}

// Put debug output into the stream "stream" to be displayed in the main window
void star_tool::set_text(std::stringstream& stream)
{
    stream << "Tool: Star (" << num_points << " points) - click and drag mouse to draw, +/- to change point count";
}

// Increment the number of points for the star
void star_tool::increment_points()
{
    num_points = std::min(20, num_points + 1); // Limit to max 20 points
}

// Decrement the number of points for the star
void star_tool::decrement_points()
{
    num_points = std::max(3, num_points - 1); // Minimum 3 points
}

// Get current number of points
int star_tool::get_num_points() const
{
    return num_points;
}
