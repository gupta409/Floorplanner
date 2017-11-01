class block {
public:

	// Details of the block
	string blockName;
	bool isSoft; // true for a soft-macro and null for a hard-macro
	float length;
	float width;
	float area;

	// To keep track of slicing tree for incremental cost update
	block* parentBlock;
	block* leftChild;
	block* rightChild;

	// For soft-macros only otherwise NULL
	float minAspectRatio;
	float maxAspectRatio;
	float optimalAspectRatio; // the optimal aspect ratio chosen among 1, minAspectRatio and maxAspectRatio

	//To print the coordinates of each block.
	float xCoordinate; // lower left
	float yCoordinate; // lower left

	//Constrcutor to create new objects
	block(string blockName, bool isSoft, float length, float width);

};
