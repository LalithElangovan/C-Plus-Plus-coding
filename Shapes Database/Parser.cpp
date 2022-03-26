
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape **shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// helper functions you write here
void command_maxShapes(string &l, stringstream &linestream);
void command_create(string &k, stringstream &linestream);
void create_Shape(string &name, string &type, int loc_x, int loc_y, int size_x, int size_y);
void command_move(string &l, stringstream &linestream);
void command_rotate(string &l, stringstream &linestream);
void command_draw(string &m, stringstream &linestream);
void command_delete(string &m, stringstream &linestream);
bool check_Command(string s);
bool check_shapename_exists(string s);
bool check_invalidname(string s);
bool shapeType(string s);
bool shapeNotFound(string s);
bool fullArray();
bool invalidValueRotate(int n);
bool invalidValueCircles(int n, int m);
bool invalidValueLocation(int n);
bool check_all(string s);

int main()
{

    string line;
    string command;

    cout << "> ";       // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof())
    {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        check_Command(command);
        if (check_Command)
        {
            command_maxShapes(command, lineStream);
            command_create(command, lineStream);
            command_move(command, lineStream);
            command_rotate(command, lineStream);
            command_draw(command, lineStream);
            command_delete(command, lineStream);
        }
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);
        command = "";
    } // End input loop until EOF.

    return 0;
}

// All commands to run the code
void command_maxShapes(string &l, stringstream &lineStream)
{
    if (l == "maxShapes")
    {
        bool more = false;
        int value;
        if ((lineStream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }

        if (shapesArray != NULL)
        {
            for (int h = 0; h < shapeCount; h++)
            {
                if (shapesArray[h]!=NULL)
                {
                    delete shapesArray[h];
                    shapesArray[h] = NULL;
                }
            }
                delete [] shapesArray;
                shapesArray = NULL;
        }

        lineStream >> value;
        if (!lineStream.fail())
        {
            int x=lineStream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
            max_shapes = value;
        }

        else if (lineStream.fail())
        {
            if (lineStream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            else
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
        }
        if (!invalidValueLocation(value))
            return;

        lineStream >> ws;
        if (lineStream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }

        cout << "New database: max shapes is " << max_shapes << endl;
        shapesArray = new Shape *[max_shapes];
        shapeCount = 0;
    }
}

void create_Shape(string &name, string &type, int loc_x, int loc_y, int size_x, int size_y)
{
    if (fullArray() && (type != "circle"))
    {
        shapesArray[shapeCount] = new Shape(name, type, loc_x, loc_y, size_x, size_y);
        shapeCount++;
        cout << "Created " << name << ':' << ' ' << type << ' ' << loc_x << ' ' << loc_y << ' ' << size_x << ' ' << size_y << endl;
        return;
    }
    else if (fullArray() && (type == "circle"))
    {
        if (!invalidValueCircles(size_x, size_y))
            return;
        shapesArray[shapeCount] = new Shape(name, type, loc_x, loc_y, size_x, size_y);
        shapeCount++;
        cout << "Created " << name << ':' << ' ' << type << ' ' << loc_x << ' ' << loc_y << ' ' << size_x << ' ' << size_y << endl;
        return;
    }
}

void command_create(string &k, stringstream &linestream)
{
    if (k == "create")
    {
        bool more = false;
        string name, type;
        int loc_x, loc_y, size_x, size_y;

        if ((linestream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }

        linestream >> name;
        if (!check_invalidname(name))
            return;
        if (!check_shapename_exists(name))
            return;
        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }

        linestream >> type;
        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!shapeType(type))
            return;

        linestream >> loc_x;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(loc_x))
            return;

        linestream >> loc_y;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(loc_y))
            return;

        linestream >> size_x;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(size_x))
            return;

        linestream >> size_y;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(size_y))
            return;

        linestream >> ws;
        int dump = linestream.peek();
        if (linestream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (more)
        {
            if (!fullArray())
                return;
            create_Shape(name, type, loc_x, loc_y, size_x, size_y);
        }
    }
}

void command_move(string &l, stringstream &linestream)
{
    if (l == "move")
    {
        bool more = false;
        string name;
        int loc_x, loc_y;

        if ((linestream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }

        linestream >> name;
        if (!check_invalidname(name))
            return;
        if (shapeNotFound(name))
            return;
        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }

        linestream >> loc_x;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(loc_x))
            return;

        linestream >> loc_y;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueLocation(loc_y))
            return;

        linestream >> ws;
        if (linestream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }
        if (more)
        {
            for (int i = 0; i < shapeCount; i++)
            {
                if (shapesArray[i]!=NULL)
                {
                    if (shapesArray[i]->getName() == name)
                    {
                        shapesArray[i]->setXlocation(loc_x);
                        shapesArray[i]->setYlocation(loc_y);
                    }
                }
            }
            cout << "Moved " << name << ' ' << "to " << loc_x << ' ' << loc_y << endl;
        }
    }
}

void command_rotate(string &l, stringstream &linestream)
{
    if (l == "rotate")
    {
        bool more = false;
        string name;
        int angle;

        if ((linestream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }
        
        linestream >> name;
        if (!check_invalidname(name))
            return;
        if (shapeNotFound(name))
            return;
        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }

        linestream >> angle;
        if (!linestream.fail()){
            int x=linestream.peek();
            if (!(x == ' ' || x == '\t' || x == EOF))
            {
                cout << "Error: invalid argument" << endl;
                return;
            }
            more = true;
        }    
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!invalidValueRotate(angle))
        {
            return;
        }


        linestream >> ws;
        if (linestream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (more)
        {
            for (int j = 0; j < max_shapes; j++)
            {
                if (shapesArray[j]!=NULL)
                {
                    if (shapesArray[j]->getName() == name)
                        shapesArray[j]->setRotate(angle);
                }
            }
            cout << "Rotated " << name << ' ' << "by " << angle <<' '<<"degrees"<<endl;
        }
    }
}

void command_draw(string &m, stringstream &linestream)
{
    if (m == "draw")
    {
        bool more = false;
        string name;
        if ((linestream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }
        linestream >> name;
        if (!check_all(name)){
            return;
        }    
        if(shapeNotFound(name))
            return;

        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }

        linestream >> ws;
        if (linestream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (name == "all" && more)
        {
            cout << "Drew all shapes" << endl;
            for (int h = 0; h < shapeCount; h++)
            {
                if (shapesArray[h]!=NULL)
                {
                    shapesArray[h]->draw();
                    cout << endl;
                }
            }
        }

        else if (more)
        {
            for (int j = 0; j < shapeCount; j++)
            {
                if (shapesArray[j] != nullptr)
                {
                    if (shapesArray[j]->getName() == name) {
                        cout << "Drew ";
                    shapesArray[j]->draw();
                    }
                }
            }
            cout << endl;
        }
    }
}

void command_delete(string &m, stringstream &linestream)
{
    if (m == "delete")
    {
        bool more = false;
        string name;

        if ((linestream >> ws).eof())
        {
            cout << "Error: too few arguments" << endl;
            return;
        }

        linestream >> name;
        if (!check_all(name)){
            return;
        }
        if(shapeNotFound(name))
            return;
        if (!linestream.fail())
            more = true;
        else if (linestream.fail())
        {
            if (linestream.eof())
            {
                cout << "Error: too few arguments" << endl;
                return;
            }
            cout << "Error: invalid argument" << endl;
            return;
        }

        linestream >> ws;
        if (linestream.peek() != EOF)
        {
            cout << "Error: too many arguments" << endl;
            return;
        }

        else if (name == "all" && more)
        {
            for (int h = 0; h < shapeCount; h++)
            {
                if (shapesArray[h] != nullptr)
                {
                    delete shapesArray[h];
                    shapesArray[h] = NULL;
                }
            }
                cout << "Deleted: all shapes" << endl;
                shapeCount = 0;
                return;
        }

        else if (more)
        {
            for (int j = 0; j < shapeCount; j++)
            {
                if (shapesArray[j]!=nullptr)
                {
                    if (shapesArray[j]->getName() == name)
                    {
                        delete shapesArray[j];
                        shapesArray[j] = NULL;
                    }
                }
            }
                    cout << "Deleted shape " << name << endl;
                    return;
        }
    }
}
// All helper functions for error checking are listed here,
// 1=invalid argument

// 7=too many arguments
// 8=too few arguments
// anything with argument was where peek was used
bool check_Command(string s)
{
    for (int i = 0; i < 7; i++)
    {
        if (s == keyWordsList[i]&&s!="all")
            return true;
    }
    cout << "Error: invalid command" << endl;
    return false;
}

// 2=invalid shape name
bool check_invalidname(string s)
{
    bool valid = true;
    for (int i = 0; i < 7; i++)
    {
        if (s == keyWordsList[i])
        {
            valid = false;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        if (s == shapeTypesList[j])
        {
            valid = false;
        }
    }
    if (!valid)
    {
        cout << "Error: invalid shape name" << endl;
    }
    return valid;
}
// 3=shape name exists
bool check_shapename_exists(string s)
{
    bool judge = true;
    for (int i = 0; i < shapeCount; i++)
    {
        if (shapesArray[i]!=nullptr)
        {
            if (s == shapesArray[i]->getName())
                judge = false;
        }
    }
    if (!judge)
    {
        cout << "Error: shape " << s << ' ' << "exists" << endl;
    }
    return judge;
}
// 4=shape name not found
bool shapeNotFound(string s)
{
    bool verdict = true;
    for (int k = 0; k < shapeCount; k++)
    {
        if (shapesArray[k] != nullptr)
        {
            if (s == shapesArray[k]->getName())
            {
                verdict = false;
            }
        }
    }
    if(s=="all")
        verdict=false;
    if (verdict)
    {
        cout << "Error: shape " << s << ' ' << "not found" << endl;
    }
    return verdict;
}
// 5=invalid shape type
bool shapeType(string s)
{
    bool judge = false;
    for (int l = 0; l < 4; l++)
    {
        if (s == shapeTypesList[l])
        {
            judge = true;
        }
    }
    
    if (!judge)
    {
        cout << "Error: invalid shape type" << endl;
    }
    return judge;
}

// 9=shape array is full
bool fullArray()
{
    bool judge = true;
    if (shapeCount >= max_shapes)
    {
        judge = false;
    }
    if (!judge)
    {
        cout << "Error: shape array is full" << endl;
    }
    return judge;
}

bool invalidValueLocation(int n)
{
    bool judge = true;
    if (n < 0)
    {
        judge = false;
    }
    if (!judge)
    {
        cout << "Error: invalid value" << endl;
    }
    return judge;
}

bool invalidValueRotate(int n)
{
    bool judge = true;
    if (n < 0 || n > 360)
    {
        judge = false;
    }
    if (!judge)
    {
        cout << "Error: invalid value" << endl;
    }
    return judge;
}

bool invalidValueCircles(int n, int m)
{
    bool judge = true;
    if (n != m)
    {
        judge = false;
    }
    if (!judge)
    {
        cout << "Error: invalid value" << endl;
    }
    return judge;
}


bool check_all(string s)
{
    bool valid = true;
    for (int i = 1; i < 7; i++)
    {
        if (s == keyWordsList[i])
        {
            valid = false;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        if (s == shapeTypesList[j])
        {
            valid = false;
        }
    }
    if (!valid)
    {
        cout << "Error: invalid shape name" << endl;
    }
    return valid;
}
