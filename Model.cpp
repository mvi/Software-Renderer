#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Model.h"
#include "Matrix.h"

vector<char*> SplitLineDown(char*, const char *);

Model::Model(void)
{
}
Model::Model(char* filename)
{
	char line[100];
	vector<string> tokens;
	ifstream filestream (filename);

	int comments = 0;
	int faces = 0;
	int mtllibs = 0;
	int objects = 0;
	int groups = 0;
	int usemtls = 0;
	int smoothingtoggles = 0;
	int others = 0;

	vector<Vector3> vertexBuffer;
	vector<Vector3> normalBuffer;
	vector<Vector3> texturecoordinateBuffer;
	vector<INT3> indexBuffer;


	bool donewithvertices = FALSE;
	char* currentmeshname;
	int linenumber = 0;

	if (filestream.is_open())
	{
		while (!filestream.eof())
		{
			filestream.getline(line,100);
			linenumber++;
			vector<char*> elems = SplitLineDown(line, " ");
			
			if(elems.size() > 0)
			{
				if(strcmp(elems[0],"#") == 0)
					comments++;
				else if (strcmp(elems[0],"v") == 0)
				{
					if(donewithvertices == TRUE)
					{
						meshes.push_back(Mesh(currentmeshname,vertexBuffer,normalBuffer,texturecoordinateBuffer,indexBuffer));
						vertexBuffer.clear();
						normalBuffer.clear();
						texturecoordinateBuffer.clear();
						indexBuffer.clear();
						donewithvertices = FALSE;
					}
					Vector3 vertexposition = Vector3(atof(elems[1]),atof(elems[2]),atof(elems[3]));
					vertexBuffer.push_back(vertexposition);

					
				}
				else if (strcmp(elems[0],"vt") == 0)
				{
					Vector3 texturecoordinate = Vector3(atof(elems[1]),atof(elems[2]),atof(elems[3]));
					texturecoordinateBuffer.push_back(texturecoordinate);
				}
				else if (strcmp(elems[0],"vn") == 0)
				{
					Vector3 normal = Vector3(atof(elems[1]),atof(elems[2]),atof(elems[3]));
					normalBuffer.push_back(normal);
				}
				else if (strcmp(elems[0],"f") == 0)
				{
					INT3 index = INT3();

					vector<char*> subelems = SplitLineDown(elems[1], "/");
					index.x = atof(subelems[0]);
					subelems = SplitLineDown(elems[2], "/");
					index.y = atof(subelems[0]);
					subelems = SplitLineDown(elems[3], "/");
					index.z = atof(subelems[0]);

					indexBuffer.push_back(index);

					faces++;
				}
				else if (strcmp(elems[0],"g") == 0)
				{
					//Set To Commit vertices to mesh on next opportunity
					donewithvertices = TRUE;


					if(elems.size() > 1)				
					{
						currentmeshname = new char[strlen(elems[1])];
                        strcpy(currentmeshname, elems[1]);
					}
					else
						currentmeshname = "";

					groups++;
				}
				else
					others++;
			}

		}

		if(donewithvertices == TRUE)
		{
			meshes.push_back(Mesh(currentmeshname,vertexBuffer,normalBuffer,texturecoordinateBuffer,indexBuffer));
			vertexBuffer.clear();
			normalBuffer.clear();
			texturecoordinateBuffer.clear();
			indexBuffer.clear();
			donewithvertices = FALSE;
		}
	}

	

	cout << "Model File Read" << endl;
	
	char vertexcountstring[50];

//	sprintf(vertexcountstring,"%d",Model::vertexBuffer.size());

//	cout << "Vertices: " << vertexcountstring << endl;

}

Model::~Model(void)
{
}

vector<char*> SplitLineDown(char* line, const char * delim)
{
	vector<char*> elems ;
	
	char* element = strtok(line, delim);

	while(element != NULL)
	{
		elems.push_back(element);
		element = strtok(NULL, delim);		
	}

	return elems;

}

