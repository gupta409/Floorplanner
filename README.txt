Gameplan:
1.Simulated Annealing
	Solution Set - datastructure
	Temperature CoolDown - function
	Perturb	-> Move	-function
		Wong-Liu Moves -logic
	Cost Calculation	- function
	AcceptMove -function
2.Convert Solution(Polish Experssion) to Node format? - function
3.Node Sizing - function
	Horizontal Node	
	Vertical Node
----------------------------------------------------------
Units:
1. Parser
	Input -> Object
	Floorplan -> Output
2. NodeSizing(Node1, Node 2, CutType)
	Make changes in optimum size parameter in both of the node1 and node 2
	return null
3. PolishtoTree("PolishExperssion")
	Make noded tree from expression
	return startingNode
3. CostCalculator(startingNode)
	traverseTree
	find node sizing at leafs as well as cuts
	find total area using sizing of root node
	return: starting node
4. AcceptanceFunction(delCost, Temperature)
	return: True/False
5. Move(currentPolish)
	return: newPolish
6. CoolDown(Temperature)
	return: newTemperature
7. SimulatedAnnealing()
	Move
	PolishToTreeConverstion
	CostCalculation
	AcceptMove
	CoolDown
	return: finalTreeStartingNode
---------------------------------------------------------------
Datastructure:
Node:
	NodeType: Soft or Hard
	SoftMinArea
	SoftMinAspect
	SoftMaxAspect
	CutType = 1(vertical), 2(horizontal), 3(endNode)
	Left*
	Right*
	Set<Size> options
	Size optimumOption
Size:
	Length
	Width
--------------------------------------------------------------
	test