#include "Maze.h"

std::vector<int> v[100000];

Maze::Maze(int width, int height) : width(width), height(height), grid(height, std::vector<Cell>(width, Cell::Wall)), gen(rd()), unlocked(false), enemynumber(0)
{
	wall_texture.loadFromFile("wall.png");
	key_texture.loadFromFile("key2.png");
	potion_texture.loadFromFile("potion.png");
	spike_texture.loadFromFile("trap.png");
	trophy_texture.loadFromFile("trophy.png");
	portal_texture.loadFromFile("portal.png");
	door_texture.loadFromFile("keyhole.png");
	floor_texture.loadFromFile("floor.png");
}

Cell Maze::getCell(int y, int x) const
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return grid[y][x];
	}
	return Cell::Wall; // Return Wall if out of bounds
}

void Maze::generatePassages(int x, int y)
{
	grid[y][x] = Cell::Passage;

	std::vector<int> dirs = { 0, 1, 2, 3 };
	std::shuffle(dirs.begin(), dirs.end(), gen);

	for (int dir : dirs)
	{
		int nx = x + dx[dir] * 2;
		int ny = y + dy[dir] * 2;

		if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx] == Cell::Wall)
		{
			grid[y + dy[dir]][x + dx[dir]] = Cell::Passage;
			generatePassages(nx, ny);
		}
	}
}

void Maze::generateMaze()
{
	generatePassages(1, 1);

	std::uniform_int_distribution<> roomWidthDist(3, 5);
	std::uniform_int_distribution<> roomHeightDist(3, 5);
	std::uniform_int_distribution<> roomXDist(1, width - 6);
	std::uniform_int_distribution<> roomYDist(1, height - 6);

	for (int i = 0; i < 3; ++i)
	{
		Room room;
		room.width = roomWidthDist(gen);
		room.height = roomHeightDist(gen);
		room.x = roomXDist(gen);
		room.y = roomYDist(gen);

		rooms.push_back(room);

		for (int y = room.y; y < room.y + room.height; ++y)
		{
			for (int x = room.x; x < room.x + room.width; ++x)
			{
				grid[y][x] = Cell::Passage;
			}
		}
	}
	for (int j = 1; j < 19; j++) {
		for (int i = 1; i < 19; i++) {
			if (grid[j][i] != Cell::Wall) {
				if (grid[j + 1][i] != Cell::Wall) {
					v[(j + 1) * 20 + i].push_back(j * 20 + i);
					v[j * 20 + i].push_back((j + 1) * 20 + i);
				}
				if (grid[j - 1][i] != Cell::Wall) {
					v[(j - 1) * 20 + i].push_back(j * 20 + i);
					v[j * 20 + i].push_back((j - 1) * 20 + i);
				}
				if (grid[j][i + 1] != Cell::Wall) {
					v[(j) * 20 + i + 1].push_back(j * 20 + i);
					v[j * 20 + i].push_back((j) * 20 + i + 1);
				}
				if (grid[j][i - 1] != Cell::Wall) {
					v[(j) * 20 + i - 1].push_back(j * 20 + i);
					v[j * 20 + i].push_back((j) * 20 + i - 1);
				}
			}
		}
	}

	std::uniform_int_distribution<> keyroompicker(0, 2);
	int keyroom = keyroompicker(gen);

	std::uniform_int_distribution<> elixercounter(1, 3);
	int elixercount = elixercounter(gen);
	for (int i = 0; i < elixercount; i++)
	{
		std::uniform_int_distribution<> posixer(0, rooms[keyroom].width);
		std::uniform_int_distribution<> posiyer(0, rooms[keyroom].height);
		int posix = posixer(gen);
		int posiy = posiyer(gen);

		if (grid[posiy + rooms[keyroom].y][posix + rooms[keyroom].x] == Cell::Key)
		{
			if (posiy = rooms[keyroom].y)
			{
				grid[posiy + rooms[keyroom].y - 1][posix + rooms[keyroom].x] = Cell::Elixer;
			}
			else
			{
				grid[posiy + rooms[keyroom].y + 1][posix + rooms[keyroom].x] = Cell::Elixer;
			}
		}
		else
		{
			grid[posiy + rooms[keyroom].y][posix + rooms[keyroom].x] = Cell::Elixer;
		}
	}

	std::uniform_int_distribution<> trophyCounter(1, 3);
	std::uniform_int_distribution<> heightrand2(0, rooms[keyroom].height);
	std::uniform_int_distribution<> widthrand2(0, rooms[keyroom].width);

	int trophycount = trophyCounter(gen);

	for (int i = 0; i < trophycount; i++)
	{
		int roomnr = keyroompicker(gen);

		std::uniform_int_distribution<> posixer(0, rooms[roomnr].width);
		std::uniform_int_distribution<> posiyer(0, rooms[roomnr].height);
		int posix = posixer(gen);
		int posiy = posiyer(gen);

		if (grid[posiy + rooms[roomnr].y][posix + rooms[roomnr].x] == Cell::Key)
		{
			if (posiy = rooms[roomnr].y)
			{
				grid[posiy + rooms[roomnr].y - 1][posix + rooms[roomnr].x] = Cell::Trophy;
			}
			else
			{
				grid[posiy + rooms[roomnr].y + 1][posix + rooms[roomnr].x] = Cell::Trophy;
			}
		}
		else
		{
			grid[posiy + rooms[keyroom].y][posix + rooms[keyroom].x] = Cell::Trophy;
		}
	}

	std::uniform_int_distribution<> heightrand(0, rooms[keyroom].height);
	std::uniform_int_distribution<> widthrand(0, rooms[keyroom].width);
	int keyposiy = rooms[keyroom].y + heightrand(gen);
	int keyposix = rooms[keyroom].x + widthrand(gen);

	grid[keyposiy][keyposix] = Cell::Key;
	keypositionx = keyposix;
	keypositiony = keyposiy;



	if (grid[keyposiy + 1][keyposix] == Cell::Wall && grid[keyposiy][keyposix + 1] == Cell::Wall && grid[keyposiy - 1][keyposix] == Cell::Wall && grid[keyposiy][keyposix - 1] == Cell::Wall)
	{
		grid[keyposiy - 1][keyposix] = Cell::Passage;
	}

	std::uniform_int_distribution<> traprand(1, 4);
	int trapamount = traprand(gen);
	trapcount = trapamount;
	Cell whichCell = Cell::Wall;
	spikelist = std::vector<Spike>(trapamount);

	for (int i = 0; i < trapamount; i++)
	{
		whichCell = Cell::Wall;
		while (whichCell == Cell::Wall)
		{
			std::uniform_int_distribution<> posixrand(0, 19);
			std::uniform_int_distribution<> posiyrand(0, 19);

			int newxposi = posixrand(gen);
			int newyposi = posiyrand(gen);

			if (grid[newyposi][newxposi] == Cell::Passage)
			{
				grid[newyposi][newxposi] = Cell::SpikeFloor;
				whichCell = Cell::Passage;
				spikelist[i].xposition = newxposi;
				spikelist[i].yposition = newyposi;
				spikelist[i].discovered = false;
				spikelist[i].damagePool = 10;
			}
		}
	}

	grid[19][19] = Cell::End;
	grid[18][19] = Cell::Door;
	grid[17][19] = Cell::Passage;
	grid[18][18] = Cell::Passage;
	grid[19][18] = Cell::Door;
	grid[19][17] = Cell::Passage;


}

/*void showpath(int x, int y) {
	int edge = y * 20 + x;
	int exit = 19 * 20 + 19;
	std::queue<std::pair<int, std::queue<int> > > q;
	std::queue<int> k;
	q.push({ edge,k });
	while (!q.empty()) {
		int w = q.front().first;
		std::queue<int> Q = q.front().second;
		Q.push(w);
		q.pop();

		for (int i = 0;i < v[w].size();i++) {
			if (!vis[v[w][i]] ) {
				vis[v[w][i]] = true;
				q.push({ v[w][i], Q });
				if (v[w][i] == exit) {
					while (!Q.empty()) {
						int p = Q.front();
						Q.pop();
						int x = p % 20;
						int y = p / 20;
						QQ = Q;
						//Player::maze.getCell(y, x).setColor(sf::Color::Yellow);
					}
					for (int j = 0;j < 10000;j++) {
						vis[j] = false;
					}
					goto end;
				}
			}
		}
	}
end:
	int yr;
}*/

void Maze::draw(sf::RenderWindow& window, float blockSize) const
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			sf::Sprite block;
			block.setScale(0.1f, 0.1f);
			//sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
			block.setPosition(x * blockSize, y * blockSize);
			switch (grid[y][x])
			{
			case Cell::Wall:
				block.setTexture(wall_texture);
				break;
			case Cell::Passage:
				block.setTexture(floor_texture);
				break;
			case Cell::End:
				block.setTexture(portal_texture);
				break;
			case Cell::Door:
				block.setTexture(door_texture);
				break;
			case Cell::Key:
				block.setTexture(key_texture);
				break;
			case Cell::Elixer:
				block.setTexture(potion_texture);
				break;
			case Cell::SpikeFloor:
				for (int i = 0; i < trapcount; i++)
				{
					if (spikelist[i].xposition == x && spikelist[i].yposition == y)
					{
						if (spikelist[i].discovered == true)
						{
							block.setTexture(spike_texture);
						}
						else
						{
							block.setTexture(floor_texture);
						}
					}
				}
				break;
			case Cell::Trophy:
				block.setTexture(trophy_texture);
				break;
			default:
				// Handle any other cases here
				break;
			}

			sf::RenderStates states;
			states.blendMode = sf::BlendAlpha;
			window.draw(block, states);
		}
	}

	/*while (!QQ.empty()) {
		int p = QQ.front();
		QQ.pop();
		int x = p % 20;
		int y = p / 20;
		sf::RectangleShape block;
		block.setSize(sf::Vector2f(20.0f, 20.0f));
		block.setFillColor(sf::Color::Yellow);
		block.setPosition(sf::Vector2f(50 * x, 50 * y));
		window.draw(block);
	}*/
}

void Maze::handleInput(sf::RectangleShape& body)
{
	/*sf::Vector2f position = body.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {

		showpath(floor(position.x * 20 / 100), floor(position.y * 20 / 100));
	}*/
}

const std::vector<Room>& Maze::getRooms() const
{
	return rooms;
}

float Maze::Cell_SDF(sf::Vector2f p, sf::Vector2f t, float size)
{
	sf::Vector2f d = sf::Vector2f(std::abs((p.x + size / 2) - (t.x + 25.f)), std::abs((p.y + size/2) - (t.y + 25.f))) - sf::Vector2f(25.f + size/2, 25.f + size/2);
	return length(max(d, 0.0f)) + min(std::max(d.x, d.y), 0.0f);
}
