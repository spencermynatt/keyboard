
const int M = 20; // row
const int N = 10; // column
//can store 200 things

int field[M][N] = { 
	0
};
struct Point {
	int x;
	int y;
}
a[4], b[4];

int figures[7][4]{
	1, 3, 5, 7,
	2, 4, 5, 7,   // different combines of positions of squares to fuse together
	3, 5, 4, 6,
	3, 5, 4, 7,
	2, 3, 5, 7,
	3, 5, 7, 6,
	2, 3, 4, 5,


};

bool check() {
	for(int i = 0; i < 4; i++)
		if(a[i].x < 0 || a[i].x >= N || a[i].y >= M)
		{
			// if x in a[] is less than 0 or x is bigger  or equal than 10
			//or if y in a[] is bigger or equal than 20
			return 0;
		}
		else if (field[a[i].y][a[i].x])
		{
			//does not mean it returned right
			return 1;
		}
};


int main()
{
	std::cout << a[0].x << std::endl;
	std::cout << a[1].x << std::endl;
	std::cout << a[2].x << std::endl;
	std::cout << a[3].x << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << a[0].y << std::endl;
	std::cout << a[1].y << std::endl;
	std::cout << a[2].y << std::endl;
	std::cout << a[3].y << std::endl;
	std::cout << "without anything happening" << std::endl;
	std::cout << "-----------" << std::endl;

	sf::Texture tiles;
	tiles.loadFromFile("C:\\Users\\Administrator\\source\\repos\\sfml_2\\Debug\\graphics\\tiles.png");
	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
	sf::Event input;//input objject
	sf::Sprite s;
	s.setPosition(100, 100);
	s.setTexture(tiles);      // a  b  c  d                   
	s.setTextureRect(sf::IntRect(0, 0, 18, 18));

	int x_axis = 0;
	bool rotate = 0;
	int colorNum = 1;
	float timer = 0;
	float delay = 0.2;
	sf::Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		//amount of time that passes from start to finish
		clock.restart();
		timer = time + timer;
		//time + 0 equals our new timer
		while (window.pollEvent(input)) //run our input
		{
			//if our event union type equals type closed
			//then it will close the window
			if (input.type == sf::Event::Closed)
			{
				window.close();
			}

			if (input.type == sf::Event::KeyPressed)
			{

				if (input.key.code == sf::Keyboard::Up) {
					rotate = true; //checks for rotation
					std::cout << "up key pressed" << std::endl;
				}
				else if (input.key.code == sf::Keyboard::Left) {
					x_axis = -1; // negates
					std::cout << "left key pressed" << std::endl;
				}
				else if (input.key.code == sf::Keyboard::Right) {
					x_axis = 1;
					std::cout << "right key pressed" << std::endl;
				}
			}
		}

		// update position
		// initially it x axis is zero because we haven't incorporated our loop


		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x = a[i].x + x_axis; // loops through a 4 times
			//adds the new position depending on our input to each item in array
			//does not move any of the squares by changing the y axis
			// so it does not move down and it stays in one y interecept
			//DEPENDING on input each value in a will add 1 or -1


		}

		if (!check()) //if this is false
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}

		//rotate
		if (rotate) {

			//we're saying that p equals a[1].x and a[1;].y so everything
			//	A[1] happens the be the square on the second line of the graph that never moves
			// this will be our center of rotation
			Point p = a[1]; // center of rotation, it does not move at all when it changes
			// the location of a[1] is the middle square so its saying
			// p equals a[1].x and a[1].y its just saying it equals the middle square
			std::cout << "this is a[1]" << std::endl;
			std::cout << a[1].x << std::endl;
			std::cout << a[1].y << std::endl;
			std::cout << "------------" << std::endl;
			std::cout << p.x << std::endl; // this changes
			std::cout << "is x axis" << std::endl;
			std::cout << "------------" << std::endl;
			std::cout << p.y << std::endl; // this stays at two
			std::cout << "is y axis" << std::endl;
			std::cout << "------------" << std::endl;


			for (int i = 0; i < 4; i++) {
				//if the player hits the up key....
				//new variable x equals
				//  a[each value looped 4 times] minus center of rotation a[1] which is always constant 2
				int x = a[i].y - p.y;
				// x = a[1, 2, 2, 3]  so since p.y = a[1].y we subtract 2
				// 1 - 1, 2, 2, 3, 
				// 0, -1, -1, -2,
				// p.y = a[1] so naturally since a gets x and y
				// p does too. So we're saying p equals x and y for 1 location of array a
				//we're saying in here	to subtract the y a[1] which is 2



				int y = a[i].x - p.x; //
				// y =  1, 1, 0, 1 - 1 each time
				// 0, 0, -1, 2
				a[i].x = p.x - x;
				//then we subtract = 1 - 0, +1, +1 +2
				//0, 2, 2, 3
				a[i].y = p.y + y;
				// 2 + 0, 0, -1, 2
				// 2, 2, 1, 4
				//final result, 0, 2, 2, 3 * 18,   2, 2, 1, 4 * 18
			}
			if (!check())
				for (int i = 0; i < 4; i++) {
					a[i] = b[i];
				}
		}
		// tick
		if (timer > delay) //if elapsed time is bigger than 0.3 
		{
			for (int i = 0; i < 4; i++) //loop through each A
			{
				b[i] = a[i];
				a[i].y = a[i].y + 1; //update y so it increases down
				 //then after its down set it back to zero.
				if (!check()) {
					for (int i = 0; i < 4; i++) {
						field[b[i].y][b[i].x] = colorNum;
						colorNum = 1 + rand() % 7;
						int n = rand() % 7;
						for (int i = 0; i < 4; i++)
						{
							a[i].x = figures[n][i] % 2;
							a[i].y = figures[n][i] / 2;
						}
					}
				}
			}

			timer = 0;

		}

		//set everything to a reasonable number
		//if a[0] = 0 (which it does because we have not set it equal to figures)
		// i want you to do this code
		/*if (a[0].x == 0) {
			int n = rand()%7; //decide which row on figures we want to use
			for (int i = 0; i < 4; i++)
			{
				//loops go into array a which has a size of 4 which is the same as the loop
				//it is then set equal to multidimensional array  "figures"

				// figures[3][i is looped 4 times] and then divided by two and gives the remainder
				//the reason is because if it did not divide by two you would have this

				/*
				array a by itself = [3, 5, 4, 7]
				(since we set the row number to 3)
				then since we're looping 4 times, as i goes up each value in the column
				figures[3][0], figures[3][1], figures[3][2], etc..
				it will divide the array by 2 and give a remainder
				so a results in a = [1, 1, 0, 1]

				now, we choose a[i] and set it equal to y from struct point
				we do the same thing but we divide by two
				and get the result
				a.y = array b with dividing of 2
				a[0, 1, 1, 1];, this is so that when we set the final position,
				it won't be all in the same location


				*/
				/*
				a[i].x = figures[n][i] % 2;
			/*	a[i].y = figures[n][i] / 2;*/ //divided by 2 instead sets the y to be different
	
	
		
	//we set x_axis and rotate to zero just so that it does not change the initial position.
		x_axis = 0; rotate = 0;
		window.clear(sf::Color::White); //clears the screen each time the loop occurs so it does not print over it
		for(int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++) //loops 4 times
		{
			// 3 5 4 7 each one multiplies by 18 4 times
			// get the remainder for the x, and get division by the y
			// so for
			// test 1 we get the remainder for two
			// 3 % 2 = 1
			// 5 % 2 = 1
			// 4 % 2 = 0
			// 7 % 2 = 1
			//for test 2 we divide by 2
			// 3 / 2 = 1
			// 5 / 2 = 2
			// 4 / 2 = 2
			// 7 / 2 = 3    computer aren't mathetmaticians they aren't going to find the exact number
		//	int test1[4] = { 1, 1, 0, 1 };
			//int test2[4] = { 1, 2, 2, 3};
			//then he mulitiplies each value by 18
			//for test 1
			// 1 * 18 = 18
			// 1 * 18 = 18
			// 0 * 18 = 0
			// 1 * 18 = 18

			//for test 2
			// 1 * 18 = 18
			// 2 * 18 = 36
			// 2 * 18 = 36 
			// 3 * 18 = 54

	//		int test1[4] = { 18, 18, 0, 18 };
	//		int test2[4] = { 18, 36, 36, 54};
			if (field[i][j] == 0) continue;

		// the 18 does not change the values of the SQUARE
			// this 18 just decides on the size of the graph that the squares are spread on
			s.setPosition(a[i].x  * 18, a[i].y * 18 );  
			//they will be position
		//it will be like set an x and y for each squares
			//then draws it
		


			window.draw(s);

		}
		
		window.draw(s);
		window.display();
	}
	std::cout << "math for how set position works" << std::endl;
	


	std::cout << a[0].x << std::endl;
	std::cout << a[1].x << std::endl;
	std::cout << a[2].x << std::endl;
	std::cout << a[3].x << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << a[0].y << std::endl;
	std::cout << a[1].y << std::endl;
	std::cout << a[2].y << std::endl;
	std::cout << a[3].y << std::endl;

	std::cout << "this is px";
	



}
