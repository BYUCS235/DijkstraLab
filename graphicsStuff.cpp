#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

#define DIMX    400
#define DIMY    400

struct Punto {
    int x, y;
};

// These are the functions implemented this file
void writeImage2File(queue<int> thePath, string _mapName);
void drawPath(double theImage[DIMX][DIMY][3], queue<int> thePath);
void drawConnections(double theImage[DIMX][DIMY][3]);
void drawNodes(double theImage[DIMX][DIMY][3]);
void drawSquare(double theImage[DIMX][DIMY][3], int x, int y, int w, double r, double g, double b);
void drawSegment(double theImage[DIMX][DIMY][3], int x1, int y1, int x2, int y2, int w, double r, double g, double b);
void readMap(string _mapName);
void writeBMPFile(double theImage[DIMX][DIMY][3]);


// Some global variables :-)
vector<Punto> theCoords;
vector< vector<int> > theCosts;


void writeImage2File(queue<int> thePath, string _mapName) {
    readMap(_mapName);

    double theImage[DIMX][DIMY][3];

    // give the image background
    for (int i = 0; i < DIMX; i++) {
        for (int j = 0; j < DIMX; j++) {
            theImage[i][j][0] = 0.95;
            theImage[i][j][1] = 0.95;
            theImage[i][j][2] = 0.95;
        }
    }

    drawPath(theImage, thePath);
    drawConnections(theImage);
    drawNodes(theImage);

    writeBMPFile(theImage);
}

void drawPath(double theImage[DIMX][DIMY][3], queue<int> thePath) {
    int xmin = 99999, xmax = -99999, ymin = 99999, ymax = -99999;

    for (int i = 0; i < theCoords.size(); i++) {
        if (theCoords[i].x > xmax)
            xmax = theCoords[i].x;
        if (theCoords[i].x < xmin)
            xmin = theCoords[i].x;
        if (theCoords[i].y > ymax)
            ymax = theCoords[i].y;
        if (theCoords[i].y < ymin)
            ymin = theCoords[i].y;
    }

    if (thePath.empty())
        return;

    int nuevo, cur;
    cur = thePath.front();
    thePath.pop();
    while (!thePath.empty()) {
        nuevo = thePath.front();
        thePath.pop();
        double c1x = ((double)(theCoords[cur].x - xmin) / (double)(xmax - xmin)) * (DIMX - 40) + 20;
        double c1y = DIMY - (((double)(theCoords[cur].y - ymin) / (double)(ymax - ymin)) * (DIMY - 40) + 20);
        double c2x = ((double)(theCoords[nuevo].x - xmin) / (double)(xmax - xmin)) * (DIMX - 40) + 20;
        double c2y = DIMY - (((double)(theCoords[nuevo].y - ymin) / (double)(ymax - ymin)) * (DIMY - 40) + 20);

        drawSegment(theImage, c1x, c1y, c2x, c2y, 7, 0.2, 1.0, 0.2);

        cur = nuevo;
    }

}

void drawConnections(double theImage[DIMX][DIMY][3]) {
    int xmin = 99999, xmax = -99999, ymin = 99999, ymax = -99999;

    for (int i = 0; i < theCoords.size(); i++) {
        if (theCoords[i].x > xmax)
            xmax = theCoords[i].x;
        if (theCoords[i].x < xmin)
            xmin = theCoords[i].x;
        if (theCoords[i].y > ymax)
            ymax = theCoords[i].y;
        if (theCoords[i].y < ymin)
            ymin = theCoords[i].y;
    }

    int cmax = 0, cmin = 99999;
    for (int i = 0; i < theCoords.size(); i++) {
        for (int j = 0; j < theCoords.size(); j++) {
            if (theCosts[i][j] >= 0) {
                if (cmin > theCosts[i][j])
                    cmin = theCosts[i][j];
                if (cmax < theCosts[i][j])
                    cmax = theCosts[i][j];
            }
        }
    }

    double c;
    double base = 0.3;
    for (int i = 0; i < theCoords.size(); i++) {
        for (int j = 0; j < theCoords.size(); j++) {
            if (theCosts[i][j] >= 0) {
                double c1x = ((double)(theCoords[i].x - xmin) / (double)(xmax - xmin)) * (DIMX - 40) + 20;
                double c1y = DIMY - (((double)(theCoords[i].y - ymin) / (double)(ymax - ymin)) * (DIMY - 40) + 20);
                double c2x = ((double)(theCoords[j].x - xmin) / (double)(xmax - xmin)) * (DIMX - 40) + 20;
                double c2y = DIMY - (((double)(theCoords[j].y - ymin) / (double)(ymax - ymin)) * (DIMY - 40) + 20);

                if (cmax == cmin)
                    c = 0.0;
                else
                    c = (double)(theCosts[i][j] - cmin) / (double)(cmax - cmin);

                double r = 1.0 * c + base * (1-c);
                double g = base;
                double b = base * c + 1.0 * (1-c);

                drawSegment(theImage, c1x, c1y, c2x, c2y, 1, r, g, b);
            }
        }
    }
}

void drawNodes(double theImage[DIMX][DIMY][3]) {
    int xmin = 99999, xmax = -99999, ymin = 99999, ymax = -99999;

    for (int i = 0; i < theCoords.size(); i++) {
        if (theCoords[i].x > xmax)
            xmax = theCoords[i].x;
        if (theCoords[i].x < xmin)
            xmin = theCoords[i].x;
        if (theCoords[i].y > ymax)
            ymax = theCoords[i].y;
        if (theCoords[i].y < ymin)
            ymin = theCoords[i].y;
    }

    // cout << "xmax: " << xmax << endl;
    // cout << "ymax: " << xmin << endl;
    // cout << "xmin: " << ymax << endl;
    // cout << "ymin: " << ymin << endl;

    for (int i = 0; i < theCoords.size(); i++) {
        double cx = ((double)(theCoords[i].x - xmin) / (double)(xmax - xmin)) * (DIMX - 40) + 20;
        double cy = DIMY - (((double)(theCoords[i].y - ymin) / (double)(ymax - ymin)) * (DIMY - 40) + 20);

        //theImage[(int)cx][(int)cy][0] = 0.0;
        //theImage[(int)cx][(int)cy][1] = 0.0;
        //theImage[(int)cx][(int)cy][2] = 0.0;
        drawSquare(theImage, (int)cx, (int)cy, 3, 0.0, 0.0, 0.0);
    }

}

void drawSquare(double theImage[DIMX][DIMY][3], int x, int y, int w, double r, double g, double b) {
    for (int i = x - (w+1)/2; i <= x + (w+1)/2; i++) {
        for (int j = y - (w+1)/2; j <= y + (w+1)/2; j++) {
            theImage[i][j][0] = r;
            theImage[i][j][1] = g;
            theImage[i][j][2] = b;
        }
    }
}

void drawSegment(double theImage[DIMX][DIMY][3], int x1, int y1, int x2, int y2, int w, double r, double g, double b) {
    double inc = 0.001;
    double x, y, cx, cy;
    for (double t = 0.0; t <= 1.0; t += inc) {
        x = t * x1 + (1.0 - t) * x2;
        y = t * y1 + (1.0 - t) * y2;
        cx = (int)(x + 0.5);
        cy = (int)(y + 0.5);
        drawSquare(theImage, cx, cy, w, r, g, b);
    }
}

// reads the file and stores the data in the global variables theCoords and theCosts
void readMap(string _mapName) {
    // string filename = "../Maps/" + _mapName + ".txt";
    // ifstream input(filename);
    ifstream input(_mapName);

    if (input.fail()) {
        cout << "file " << _mapName << " does not exist" << endl;
        exit(1);
    }

    int numNodes;
    input >> numNodes;

    for (int i = 0; i < numNodes; i++) {
        vector<int> myRow;
        for (int j = 0; j < numNodes; j++) {
            int val;
            input >> val;
            myRow.push_back(val);
        }
        theCosts.push_back(myRow);
    }

    for (int i = 0; i < numNodes; i++) {
        Punto p;
        input >> p.x;
        input >> p.y;
        theCoords.push_back(p);
    }

    input.close();
}


// code in this function was modifed from code obtained at this website (obtained 8/12/2021):
//      https://newbedev.com/writing-bmp-image-in-pure-c-c-without-other-libraries
void writeBMPFile(double theImage[DIMX][DIMY][3]) {
    int w = DIMX;
    int h = DIMY;
    int x, y;
    unsigned char r, g, b;

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,3*w*h);

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            x = i;
            y = (h - 1) - j;
            r = (unsigned char)(theImage[i][j][0]*255);
            g = (unsigned char)(theImage[i][j][1]*255);
            b = (unsigned char)(theImage[i][j][2]*255);
            if (r > 255) 
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;
            img[(x+y*w)*3+2] = (unsigned char)(r);
            img[(x+y*w)*3+1] = (unsigned char)(g);
            img[(x+y*w)*3+0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen("Map.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i = 0; i < h; i++) {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

    free(img);
    fclose(f);
}
