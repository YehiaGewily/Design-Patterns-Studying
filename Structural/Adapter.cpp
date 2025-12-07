/*
 * Design Patterns - Adapter
 * Author: Yehya
 * Description: Implementation of the Adapter pattern in C++.
 */

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <cmath>
#include <boost/functional/hash.hpp>

using namespace boost;
using namespace std;

struct Point
{
	int x, y;

	friend size_t hash_value(const Point& obj)
	{
		size_t seed = 0x1E44943F;
		boost::hash_combine(seed, obj.x);
		boost::hash_combine(seed, obj.y);
		return seed;
	}
};

struct Line
{
	Point start, end;

	friend size_t hash_value(const Line& obj)
	{
		size_t seed = 0x4D274623;
		boost::hash_combine(seed, obj.start);
		boost::hash_combine(seed, obj.end);
		return seed;
	}
};

struct VectorObject
{
	virtual vector<Line>::iterator begin() = 0;
	virtual vector<Line>::iterator end() = 0;

};

struct VectorRectangle : VectorObject
{
	VectorRectangle(int x, int y, int width, int height)
	{
		lines.emplace_back(Line{ Point{x,y}, Point{x + width,y} });
		lines.emplace_back(Line{ Point{x + width,y}, Point{x + width,y + height} });
		lines.emplace_back(Line{ Point{x,y}, Point{x,y + height} });
		lines.emplace_back(Line{ Point{x,y+height}, Point{x + width,y+height}});
	}
private:
	vector<Line> lines;
};

vector<shared_ptr<VectorObject>> vectorObjects{
	make_shared<VectorRectangle>(10,10,100,100),
	make_shared<VectorRectangle>(30,30,60,60)
};

struct LineToPointAdapter
{
	typedef vector<Point> Points;

	LineToPointAdapter(Line &line) {
		static int count = 0;
		int left = min(line.start.x, line.end.x);
		int right = max(line.start.x, line.end.x);
		int top = min(line.start.y, line.end.y);
		int bottom = max(line.start.y, line.end.y);
		int dx = right - left;
		int dy = line.end.y = line.start.y;

		if (dx == 0) {

		}
	}

	virtual Points::iterator begin() { return points.begin(); }
	virtual Points::iterator end() { return points.end(); }

private:
	Points points;
};

struct LineToPointCachingAdapter
{
	typedef vector<Point> Points;

	LineToPointCachingAdapter(Line& line) {
		boost::hash<Line> hash;

		line_hash = hash(line);
		if (cache.find(line_hash) != cache.end())return;


	}

private:
	size_t line_hash;

	static map<size_t, Points> cache;
};

int main()
{

}
