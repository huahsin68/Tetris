#include "Score.h"


Score::Score()
{
    res = new Resource("../resources/font.png");

    int x = 0;
    float posY = 0.365f;
    digit1 = new Text(res, { 0.65f, posY }, { 1.077f, 0.23f });
	digit2 = new Text(res, { 0.71f, posY }, { 1.13f, 0.23f });
	digit2->setHide(true);
}

Score::~Score()
{

}

void Score::create(unsigned int shader)
{
    digit1->create(shader);
    digit2->create(shader);
}

void Score::draw()
{
    digit1->draw();
    digit2->draw();
}

void Score::increamentScore()
{
	score++;
	updateScore();

	cout << "debug score: " << score << endl;
}

void Score::updateScore()
{
	int tmpScore = score;
	int n = log10(score) + 1;

	if( n < 0 ) 
		n = 0;

	int i;
	char* numberArray = (char*)calloc(n, sizeof(char));

	for (i = n - 1; i >= 0; --i, tmpScore /= 10) {
		numberArray[i] = (tmpScore % 10) + '0';
	}

	if( score > 9 ) {
		digit1->setPosition({ 0.61f, 0.365f });
		digit1->rePosition();
		digit1->updateText(numberArray[0]);

		digit2->setHide(false);
		digit2->updateText(numberArray[1]);
	}
	else {
		digit1->setPosition({ 0.71f, 0.365f });
		digit1->updateText(numberArray[0]);
	}
}
