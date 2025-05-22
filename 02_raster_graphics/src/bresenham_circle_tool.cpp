//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_circle_tool.h"
#include <algorithm>
#include <math.h>

// Initialize the tool and store a reference of a canvas_buffer
bresenham_circle_tool::bresenham_circle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool draws circles!
	shape = TS_CIRCLE;
}



// Draw a circle with center (x0, y0) and (x1, y1) on the circle
void bresenham_circle_tool::draw(int x0, int y0, int x1, int y1)
{
	// Calculate the radius
	int r = static_cast<int>(sqrt(static_cast<double>((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1))));

	/************
	Additional task: Implement circle rasterization using the bresenham algorithm.
	                 The circle shall have its center at (x0, y0) with a
					 radius of "r".
    Zusatzaufgabe:   Implementieren Sie die Rasterisierung eines Kreises mit dem
	                 Bresenham-Algorithmus. Der Kreis soll seinen Mittelpunkt bei
					 (x0, y0) und einen Radius von "r" haben.
	*************/
    
    // Bresenham circle algorithm implementation
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    // Helper function to draw 8 symmetric points at once
    auto drawCirclePoints = [&](int cx, int cy, int x, int y) {
        canvas.set_pixel(cx + x, cy + y);
        canvas.set_pixel(cx - x, cy + y);
        canvas.set_pixel(cx + x, cy - y);
        canvas.set_pixel(cx - x, cy - y);
        canvas.set_pixel(cx + y, cy + x);
        canvas.set_pixel(cx - y, cy + x);
        canvas.set_pixel(cx + y, cy - x);
        canvas.set_pixel(cx - y, cy - x);
    };
    
    // Draw the initial points
    drawCirclePoints(x0, y0, x, y);
    
    // Main Bresenham circle loop
    while (y >= x) {
        x++;
        
        // Update the decision parameter and y
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        
        // Draw the points in the eight octants
        drawCirclePoints(x0, y0, x, y);
    }
}

// Put debug output into the stream "stream" to be displayed in the
// main window
void bresenham_circle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Bresenham-Circle (click and drag mouse to draw)";
}
