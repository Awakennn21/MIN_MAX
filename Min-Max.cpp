#include <iostream>
#define INF 99
#define PlayerX '1'
#define PlayerO '2'
#define Empty '0'

class Map
{
public:
    char** m_MapInstance;
    int m_MapSizeX, m_MapSizeY;
    int m_WinCondition;
    int m_SpacesFilled;

    Map(int MapSizeX, int MapSizeY, int WinCondition)
    {
        m_MapSizeX = MapSizeX;
        m_MapSizeY = MapSizeY;
        m_WinCondition = WinCondition;
        m_SpacesFilled = 0;

        m_MapInstance = new char* [m_MapSizeY];
        for (int i = 0; i < m_MapSizeY; i++)
        {
            m_MapInstance[i] = new char[m_MapSizeX];
            for (int j = 0; j < m_MapSizeX; j++)
            {
                m_MapInstance[i][j] = Empty;
            }
        }
    }

    void MapPrint() const
    {
        for (int i = 0; i < m_MapSizeY; i++)
        {
            for (int j = 0; j < m_MapSizeX; j++)
            {
                std::cout << m_MapInstance[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int CalculateAllOutcomes(char Player, bool GoInDepth, bool LookForAWinner, int alpha = -INF, int beta = INF)
    {
        int max = -INF;
        int min = INF;

        if (LookForAWinner)
        {
            if (LookForWinner() == 1)
            {
                return 1;
            }
            else if (LookForWinner() == 2)
            {
                return -1;
            }
            else if (LookForWinner() == 0 && MapFilled())
            {
                return 0;
            }
        }

        for (int i = 0; i < m_MapSizeY; i++)
        {
            for (int j = 0; j < m_MapSizeX; j++)
            {
                if (m_MapInstance[i][j] == Empty)
                {
                    m_MapInstance[i][j] = Player;
                    m_SpacesFilled++;

                    if (!GoInDepth)
                    {
                        MapPrint();
                    }
                    if (GoInDepth)
                    {
                        char p = Player == PlayerX ? PlayerO : PlayerX;
                        int score = CalculateAllOutcomes(p, true, true, alpha, beta);
                        if (Player == PlayerX)
                        {
                            max = score > max ? score : max;
                            alpha = score > alpha ? score : alpha;
                        }
                        else
                        {
                            min = score < min ? score : min;
                            beta = score < beta ? score : beta;
                        }
                    }
                    m_MapInstance[i][j] = Empty;
                    m_SpacesFilled--;
                }

                if (beta <= alpha)
                {
                    if (Player == PlayerX)
                    {
                        return max;
                    }
                    else
                    {
                        return min;
                    }
                }
            }
        }

        if (Player == PlayerX)
        {
            return max;
        }
        else
        {
            return min;
        }
    }

    int LookForWinner() const
    {
        for (int i = 0; i < m_MapSizeY; i++)
        {
            for (int j = 0; j < m_MapSizeX; j++)
            {
                if (m_MapInstance[i][j] == PlayerX)
                {
                    if (HowManyInRow(i, j, PlayerX) >= m_WinCondition)
                    {
                        return 1;
                    }
                }
                else if (m_MapInstance[i][j] == PlayerO)
                {
                    if (HowManyInRow(i, j, PlayerO) >= m_WinCondition)
                    {
                        return 2;
                    }
                }
            }
        }
        return 0;
    }

    int HowManyInRow(int i, int j, char Player) const
    {
        int count = 1, maxcount = 1;
        int BegI = i, BegJ = j;
        for (int di = 0; di < 2; di++)
        {
            for (int dj = -1; dj < 2; dj++)
            {
                if ((di == 0 && dj == -1) || (di == 0 && dj == 0))
                {
                    continue;
                }
                if (j + dj < m_MapSizeX && i + di < m_MapSizeY && j + dj >= 0)
                {
                    while (m_MapInstance[i + di][j + dj] == Player)
                    {
                        if ((j + dj == m_MapSizeX - 1 && dj > 0) || (i + di == m_MapSizeY - 1 && di > 0) || (j + dj == 0 && dj < 0))
                        {
                            if (m_MapInstance[i + di][j + dj] == Player)
                            {
                                count++;
                            }
                            break;
                        }
                        else if ((j + dj > m_MapSizeX - 1) || (i + di > m_MapSizeY - 1) || (j + dj < 0))
                        {
                            break;
                        }
                        i += di;
                        j += dj;
                        count++;
                    }
                    maxcount = count > maxcount ? count : maxcount;
                }
                i = BegI;
                j = BegJ;
                count = 1;
            }
        }
        return maxcount;
    }

    bool MapFilled() const
    {
        return m_SpacesFilled == (m_MapSizeX * m_MapSizeY);
    }

    ~Map()
    {
        for (int i = 0; i < m_MapSizeY; i++)
        {
            delete[] m_MapInstance[i];
        }
        delete[] m_MapInstance;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int IMapSizeX = 0, IMapSizeY = 0, IWinCondition = 0;
    char Player = PlayerX;
    char* Command = new char[90];
    while (std::cin.good())
    {
        int MoveCount = 0;
        std::cin >> Command;
        std::cin >> IMapSizeY;
        std::cin >> IMapSizeX;
        std::cin >> IWinCondition;
        std::cin >> Player;
        Map MapInstance(IMapSizeX, IMapSizeY, IWinCondition);

        for (int i = 0; i < MapInstance.m_MapSizeY; i++)
        {
            for (int j = 0; j < MapInstance.m_MapSizeX; j++)
            {
                std::cin >> MapInstance.m_MapInstance[i][j];
                if (MapInstance.m_MapInstance[i][j] == Empty)
                {
                    MoveCount++;
                }
                else
                {
                    MapInstance.m_SpacesFilled++;
                }
            }
        }
        if (strcmp(Command, "SOLVE_GAME_STATE") == 0)
        {
            int Resault = MapInstance.CalculateAllOutcomes(Player, true, true);
            if (Resault == 1)
            {
                std::cout << "WITH OPTIMAL PLAY FIRST PLAYER WINS" << std::endl;
            }
            else if (Resault == -1)
            {
                std::cout << "WITH OPTIMAL PLAY  SECOND PLAYER WINS" << std::endl;
            }
            else
            {
                std::cout << "UNWINNABLE POSITION" << std::endl;
            }
        }
    }

    delete[] Command;
}