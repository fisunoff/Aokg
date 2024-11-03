#include "Mesh.h"

Mesh::Mesh() {
	vertices = {};
	indices = {};
}
void Mesh::load(string filename) {
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	map<string, int> vertexToIndexTable;
	ifstream file(filename);
	// вектор для хранения геометрических координат
	vector<vec3> v;
	// вектор для хранения нормалей
	vector<vec3> n;
	// вектор для хранения текстурных координат
	vector<vec3> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	vector<ivec3> fPoints;
	int index = 0;
	while (!file.eof()) {
		string param;
		file >> param;
		if (param == "v") {
			float x, y, z;
			file >> x >> y >> z;
			v.push_back(vec3(x, y, z));
		}
		else if (param == "vt") {
			float x, y, z;
			file >> x >> y >> z;
			t.push_back(vec3(x, y, z));
		}
		else if (param == "vn") {
			float x, y, z;
			file >> x >> y >> z;
			n.push_back(vec3(x, y, z));
		}
		else if (param == "f") {
			string str;
			for (int i = 0; i < 3; i++)
			{
				ivec3 face;
				file >> str;
				map<string, int>::iterator iter = vertexToIndexTable.find(str);
				if (iter != vertexToIndexTable.end())
				{
					indices.push_back(iter->second);
					continue;
				}
				stringstream ss(str);
				string temp;
				getline(ss, temp, '/');
				face[0] = stoi(temp);
				getline(ss, temp, '/');
				face[1] = stoi(temp);
				getline(ss, temp, '/');
				face[2] = stoi(temp);
				vertexToIndexTable.insert(make_pair(str, index));
				indices.push_back(index++);
				fPoints.push_back(face);
			}
		}

	}
	for (glm::ivec3& index : fPoints)
	{
		Vertex vert;
		vert.coord = v[index.x - 1];
		vert.texCoord = t[index.y - 1];
		vert.normal = n[index.z - 1];

		vertices.push_back(vert);
	}
}

void Mesh::draw()
{
	if (vertices.size() == 0) return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), value_ptr(vertices[0].coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), value_ptr(vertices[0].normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), value_ptr(vertices[0].texCoord));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

};