#include "SelectBox.h"

SelectBox::SelectBox(IntRect box, Color color, bool mid)
	:vertices{TriangleStrip, 6}
	,width(box.width)
	,xChange(width / 25)
	,aChange(17)
{
	if (mid) {
		xDest = box.left + width / 2;
	}
	else {
		xDest = box.left + width / 4;
	}
	vertices[0].position = Vector2f(box.left, box.top);
	vertices[1].position = Vector2f(box.left, box.top + box.height);
	vertices[2].position = Vector2f(box.left + box.width / 4, box.top);
	vertices[3].position = Vector2f(box.left + box.width / 4, box.top + box.height);
	vertices[4].position = Vector2f(box.left + box.width, box.top);
	vertices[5].position = Vector2f(box.left + box.width, box.top + box.height);
	vertices[2].color = vertices[3].color = color;
	vertices[0].color = vertices[1].color = vertices[4].color = vertices[5].color = Color(255, 255, 255, 255);
}

SelectBox::SelectBox(Color color)
	:vertices{ TriangleStrip, 6 }
	, aChange(17)
{
	vertices[2].color = vertices[3].color = color;
	vertices[0].color = vertices[1].color = vertices[4].color = vertices[5].color = Color::Transparent;
}

void SelectBox::setAlpha(char alpha)
{
	vertices[2].color.a = vertices[3].color.a = alpha;
}

void SelectBox::fade(char alpha)
{
	if (vertices[2].color.a - alpha < 0) {
		vertices[2].color.a = vertices[3].color.a = 0;
	}
	else {
		vertices[2].color.a = vertices[3].color.a -= alpha;
	}
	//vertices[2].color.a = vertices[3].color.a -= alpha;
}

void SelectBox::select(short int x)
{
	if (vertices[2].color.a != 255) {
		fade(-aChange);
	}
	if (vertices[2].position.x - xChange > x) {
		moveCenter(-xChange);
	}
	else if (vertices[2].position.x + xChange < x) {
		moveCenter(xChange);
	}
	else {
		setCenter(x);
	}
}

void SelectBox::select()
{
	if (vertices[2].color.a != 255) {
		fade(-aChange);
	}
	if (vertices[2].position.x - xChange > xDest) {
		moveCenter(-xChange);
	}
	else if (vertices[2].position.x + xChange < xDest) {
		moveCenter(xChange);
	}
	else {
		setCenter(xDest);
	}
}

void SelectBox::deselect()
{
	if (vertices[2].color.a) {
		if (width - vertices[2].position.x < width / 5) {
			fade(3 *aChange);
		}
		else {
			fade(aChange);
		}
	}
	moveCenter(xChange);
}

void SelectBox::setCenter(short int x)
{
	if (x > vertices[5].position.x) {
		x = vertices[5].position.x - 1;
	}
	else if (x < vertices[0].position.x) {
		x = vertices[0].position.x + 1;
	}
	vertices[2].position.x = vertices[3].position.x = x;
}

void SelectBox::moveCenter(short int x)
{
	vertices[3].position.x += x;
	if (vertices[3].position.x > vertices[5].position.x) {
		vertices[3].position.x = vertices[5].position.x - 1;
	}
	else if (vertices[3].position.x < vertices[0].position.x) {
		vertices[3].position.x = vertices[0].position.x + 1;
	}
	vertices[2].position.x = vertices[3].position.x;
}

void SelectBox::setBox(IntRect box, bool mid)
{
	width = box.width;
	if (mid) {
		xDest = box.left + width / 2;
	}
	else {
		xDest = box.left + width / 4;
	}
	xChange = width / 25;
	vertices[0].position = Vector2f(box.left, box.top);
	vertices[1].position = Vector2f(box.left, box.top + box.height);
	vertices[2].position = Vector2f(box.left + box.width - 1, box.top);
	vertices[3].position = Vector2f(box.left + box.width - 1, box.top + box.height);
	vertices[4].position = Vector2f(box.left + box.width, box.top);
	vertices[5].position = Vector2f(box.left + box.width, box.top + box.height);
}

void SelectBox::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(vertices);
}
