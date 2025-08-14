/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"
#include "kdtree.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas* output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    // avg xyzpix
    vector<Point<3>> xyzpoints;
    // key-valued pair with parameter <avg color, tile>
    map<Point<3>, TileImage*> kvpair;
    for(auto i = theTiles.begin(); i != theTiles.end(); ++i){

        // stores the avg color of the tile image
        LUVAPixel luvapix = i -> getAverageColor();
        // convert it into xyz
        Point<3> xyzpix = convertToXYZ(luvapix);
        // store it to find nearest neighbor
        xyzpoints.push_back(xyzpix);
        // store the key-value pair
        kvpair[xyzpix] = &(*i);
    }

    for(int a = 0 ; a < theSource.getRows(); a++){
        for(int b = 0; b < theSource.getColumns(); b++){
            // locate the current pixel
            LUVAPixel sourceColor = theSource.getRegionColor(a, b);
            Point<3> current = convertToXYZ(sourceColor);

            // find the nearest point
            Point<3> nearest = xyzpoints[0];
            for(int j = 1; j < (int)(xyzpoints.size()); j++){
                if(shouldReplace(current, nearest, xyzpoints[j])){
                    nearest = xyzpoints[j];
                }
            }
            output -> setTile(a, b, kvpair[nearest]);
        }
    }
    return output;

}

