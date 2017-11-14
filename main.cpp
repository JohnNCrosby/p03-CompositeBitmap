//Author: John Crosby
#include<vector>
#include<string>
#include<iostream>
#include"bitmap.h"
using namespace std;

vector<Bitmap> imageList(vector<Bitmap>);

bool sizeTest(vector<Bitmap>);

void combination(vector< vector< vector<Pixel> > >, vector< vector<Pixel> > &, vector<Bitmap>);

void pixelConverter(vector<Bitmap>, vector< vector< vector<Pixel> > > &);

int main()
{
    vector <Bitmap> images;
    vector< vector< vector<Pixel> > > bmps;
    vector< vector<Pixel> > finish;
    Bitmap image;

    //Ask user for file names and store them, give them a max of 10 though allow for any amount above 1.
    //Check for errors in the bitmaps or if there isn't enough.
    images = imageList(images);
    
    
    //Put the images given into a matrix of pixels by converting them to pixel images.
    pixelConverter(images, bmps);


    //Combine the images given by the user.
    //Give updates along the way.
    combination(bmps, finish, images);
    //Saves file into a new file named composite-username.bmp.
    image.fromPixelMatrix(finish);    
    image.save("composite-jcrosby7.bmp");
    cout<<"Your images have been composited. The name for the file is composite-jcrosby7.bmp"<<endl;
    return 0;
}

vector<Bitmap> imageList(vector<Bitmap> list)
{
    Bitmap image;
    int number;
    bool validBmp, size;
    string name;
    do
    {
        cout<<"How many files do you have up to 10 but at least 2?"<<endl;
        cin>>number;
    } while(number > 10 && number < 2);

    for(int i = 0; i < number; i++)
    {
        do
        {
            cout<<"Please enter a valid bmp file name that are of the same dimension."<<endl;
            cin>>name;
            image.open(name);
            validBmp = image.isImage();
            if(validBmp == false)
            {
                cout<<"Error not an image."<<endl;
            }
        } while(validBmp == false);
        list.push_back(image);
        cout<<"Image loaded"<<endl;
    }
    cout<<"Checking dimensions"<<endl;
    size = sizeTest(list);
    if(size == true)
    {
        cout<<"Everything seems to be in order."<<endl;
        return list;
    }
    else
    {
        cout<<"Please restart the program and insert similarly sized images."<<endl;
    }

}

bool sizeTest(vector<Bitmap> test)
{
    int x = 0;
    int b = 0;
    vector<vector< Pixel> > bmp, t;
    bmp = test[0].toPixelMatrix();
    for(int i = 0; i < test.size(); i++)
    {
        t = test[i].toPixelMatrix();
        cout<<"Current images size is "<<t.size()<<" "<<t[0].size()<<endl;
        if(bmp.size() == t.size() && bmp[0].size() == t[0].size())
        {
            x++;
        }
        b++;
    }
    
    if(x == b)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void pixelConverter(vector<Bitmap> list, vector< vector< vector<Pixel> > > & bmp)
{   
    vector< vector<Pixel> > place, holder;
    Bitmap hold, held;
    hold = list[0];
    place = hold.toPixelMatrix();
    bmp.resize(place.size());
    for(int x = 0; x < place.size(); x++)
    {
        bmp[x].resize(place[0].size());
        for(int i = 0; i < list.size(); i++)
        {
            bmp[x][i].resize(list.size());
        }
    }
    cout<<bmp.size()<<" "<<bmp[0].size()<<" "<<bmp[3].size()<<" "<<bmp[3][0].size()<<endl;
    for(int i = 0; i < list.size(); i++)
    {
        held = list[i];
        holder = held.toPixelMatrix();
        for(int x = 0; x < place.size(); x++)
        {
            for(int y = 0; y < place[0].size(); y++)
            {
                //held = list[i];
                //holder = held.toPixelMatrix();
                bmp[x][y][i] = holder[x][y];
                cout<<"Test"<<endl;
            }
        }
    }
    cout<<"test"<<endl;
}

void combination(vector< vector< vector<Pixel> > > temp, vector< vector<Pixel> > & finish, vector<Bitmap> amount)
{
    Pixel rgb;
    double r, g, b;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    finish.resize(temp.size());
    for(int x = 0; x < temp.size(); x++)
    {
        finish[x].resize(temp[0].size());
    }
    for(int x = 0; x < temp.size(); x++)
    {
        for(int y = 0; y < temp[0].size(); y++)
        {
            for(int i = 0; i < amount.size(); i++)
            {
                rgb = temp[x][y][i];
                r = rgb.red + r;
                g = rgb.green + g;
                b = rgb.blue + b;
            }
            r = r/amount.size();
            g = g/amount.size();
            b = b/amount.size();
            rgb.red = r;
            rgb.green = g;
            rgb.blue = b;
            finish[x][y] = rgb;
        }
    }
}

