/******************************************************************************/
/*                          MICROORGANISM EXPERIMENTS                         */
/*																																						*/
/*	    Note: Includes a little amount of Tissue tests, Interact() method		  */
/******************************************************************************/
#include "Main.h"

int main(int argc, char* argv[]) {
	Circular* ali = new Circular(10,3);
	vector<Particle*> p;
	Tissue *tissue=NULL;
	p.push_back(new Particle(0,0));
	p.push_back(new Particle(0,3));
	p.push_back(new Particle(3,3));
	p.push_back(new Particle(3,0));
	
	vector<Wall*> walls;
	walls.push_back(new Wall(*p[0], *p[1]));
	walls.push_back(new Wall(*p[1], *p[2]));
	walls.push_back(new Wall(*p[2], *p[3]));
	walls.push_back(new Wall(*p[3], *p[0]));


	Cell* cell = new Cell(0, walls, tissue);
	vector<Particle*> q;

	q.push_back(new Particle(0,0));
	q.push_back(new Particle(3,4));
	q.push_back(new Particle(4,3));

	vector<Wall*> circleWalls;
	circleWalls.push_back(new CurvyWall(*q[1], *q[2], *q[0]));
	circleWalls.push_back(new CurvyWall(*q[2], *q[1], *q[0]));

	Cell* cellCircle = new Cell(1, circleWalls, tissue);
	
	cout<<*ali<<endl;
	cout << ali->DoesFitInto(*cellCircle)<<endl;
	cout<<*ali<<endl;
	ali->ConnectToCell(cellCircle);
	cout<<*ali<<endl;
	ali->React();
	delete cell;
	delete cellCircle;
	for (int i=0; i < walls.size(); i++)
		delete walls[i];
	for (int i=0; i < circleWalls.size(); i++)
		delete circleWalls[i];
	for (int i=0; i < p.size(); i++)
		delete p[i];
	for (int i=0; i < q.size(); i++)
		delete q[i];
	delete ali;
	/*
	// argv[1] = "input/cells.txt",	argv[2] = "input/microorganisms.txt"

	// Read MicroOrganisms
	vector<MicroOrganism*> microOrganisms = ReadMicroOrganisms(argv[2]);

	// Read Cells
	Tissue* tissue = new Tissue();
	ReadCells(argv[1], *tissue);

	// Interact microorganisms with cells
	cout << "TEST NO 7 - Tissue:: Interact() which includes MicroOrganism:: DoesFitInto() and ConnectToCell()" << endl;
	tissue->Interact(microOrganisms);
	for (int i=0; i < microOrganisms.size(); i++)
		cout << *microOrganisms[i] << endl;
	cout << "The answer key: " << endl;
	cout << "\t Microorganism 0 into Cell 6" << endl;
	cout << "\t Microorganism 1 into NONE  " << endl;
	cout << "\t Microorganism 2 into Cell 4" << endl;
	cout << "\t Microorganism 3 into Cell 2" << endl;
	cout << "\t Microorganism 4 into Cell 1" << endl;
	cout << "\t Microorganism 5 into Cell 0" << endl << endl;

	// Make microorganisms reacted
	cout << "TEST NO 8 - Microorganism:: React() " << endl;

	cout << "\t Microorganism 0 reacts:" << endl;
	microOrganisms[0]->React();																																				// A circular microorganism reaction
	cout << "Radius is: " << ((CurvyWall*)tissue->GetCell(6).GetCellWall()[0])->GetRadius() << endl;	// Did cell walls get larger?
	cout << "Center is: " << ((CurvyWall*)tissue->GetCell(6).GetCellWall()[0])->GetCenter() << endl;	// Center does not change
	cout << "Cell wall is: " << tissue->GetCell(6) << endl;																						// Any point on the cell (Assuming it is strengthened, not necessarily)
	cout << "The answer key: Radius is 10 and Center is (8,0). The rest should be fitting cell wall(s)." << endl << endl;

	cout << "\t Microorganism 2 reacts:" << endl;
	microOrganisms[2]->React();																																				// A circular microorganism reaction
	cout << "Radius is: " << ((CurvyWall*)tissue->GetCell(4).GetCellWall()[0])->GetRadius() << endl;	// Did cell walls get larger?
	cout << "Center is: " << ((CurvyWall*)tissue->GetCell(4).GetCellWall()[0])->GetCenter() << endl;	// Center does not change
	cout << "Cell wall is: " << tissue->GetCell(4) << endl;																						// Any point on the cell (Assuming it is strengthened, not necessarily)
	cout << "The answer key: Radius is 4 and Center is (1,-5). The rest should be fitting cell wall(s)." << endl << endl;

	cout << "\t Microorganism 3 reacts:" << endl;
	microOrganisms[3]->React();																																				// A triangular microorganism reaction
	try {
		const Cell cell =  tissue->GetCell(2);
	} catch (DeadCellException e) {
		cout << e.what() << endl << endl;
	}
	cout << "The answer key: Should print DeadCellException message." << endl << endl;

	cout << "\t Microorganism 4 reacts:" << endl;
	microOrganisms[4]->React();																																				// A triangular microorganism reaction
	try {
		const Cell cell =  tissue->GetCell(1);
	} catch (DeadCellException e) {
		cout << e.what() << endl << endl;
	}
	cout << "The answer key: Should print DeadCellException message." << endl << endl;

	cout << "\t Microorganism 5 reacts:" << endl;
	microOrganisms[5]->React();																																				// A squadratic microorganism reaction
	try {
		Squadratic child = ((Squadratic*)microOrganisms[5])->GetChild(1.5, 3, 0, 1.5);
		child.React();
		try {
			Squadratic grandchild = ((Squadratic*)microOrganisms[5])->GetChild(0.75, 1.5, 1.5, 2.25);
		} catch (NotBornChildException e) {
			cout << "First child request is ok, yet for the second child request you got:" << endl;
			cout << e.what() << endl << endl;
		}
	} catch (NotBornChildException e) {
		cout << "You failed in requesting the first child:" << endl;
		cout << e.what() << endl << endl;
	}
	cout << "The answer key: Should print NotBornChildException message only for the second child request." << endl << endl;

	// Test the methods which are specialized to microorganism types
	cout << "TEST NO 9 - Circular:: DoesContain() " << endl;
	Particle p(10,1);
	Particle q(-2,-5);
	cout << ((Circular*)microOrganisms[0])->DoesContain(p) << endl;
	cout << ((Circular*)microOrganisms[2])->DoesContain(p) << endl;
	cout << "The answer key: 1 | 0 " << endl << endl;


	cout << "TEST NO 10 - Triangular:: Mutate() " << endl;
	cout << "RNA before the mutation: " << ((Triangular*)microOrganisms[4])->GetRNA() << endl;
	((Triangular*)microOrganisms[4])->Mutate((Triangular&)*microOrganisms[3]);
	cout << "RNA after the mutation: " << ((Triangular*)microOrganisms[4])->GetRNA() << endl;
	cout << "The answer key: AGSGGAUUUASGAGSAAUAG should change to AGSGGAUUASGUUAG." << endl << endl;

	// Deletes
	delete tissue;
	for (int i=0; i < microOrganisms.size(); i++)
		delete microOrganisms[i];
	*/
	return 0;
}
