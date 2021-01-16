class Vector3 {
	float x, y, z;

	Vector3() {
		x = y = z = 0;
	}

	Vector3(float x, float y, float z) {
		x = x;
		y = y;
		z = z;
	}

};

class Obj {
	Vector3 position;
	Vector3 rotation;
	
	Obj(Vector3 position, Vector3 rotation) {
		position = position;
		rotation = rotation;
	}

	Obj(Vector3 position) {
		position = position;
		rotation = Vector3();
	}
};