#include "Mesh.h"

Mesh::Mesh() {
	vertices = {};
}
void Mesh::load(string filename) {
	ifstream file(filename);
	// ������ ��� �������� �������������� ���������
	vector<vec3> v;
	// ������ ��� �������� ��������
	vector<vec3> n;
	// ������ ��� �������� ���������� ���������
	vector<vec3> t;
	// ������ ��� �������� �������� ���������, ��� ���������� ������
	vector<ivec3> fPoints;
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
				stringstream ss(str);
				string temp;
				getline(ss, temp, '/');
				face[0] = stoi(temp);
				getline(ss, temp, '/');
				face[1] = stoi(temp);
				getline(ss, temp, '/');
				face[2] = stoi(temp);
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
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

};