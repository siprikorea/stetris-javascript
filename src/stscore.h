#ifndef __STSCORE_H__
#define __STSCORE_H__

#define ST_MAX_BOARD_X 10
#define ST_MAX_BOARD_Y 20

class CStScore
{
public:
    // Constructor
    CStScore();

    // Clear
    void Clear();
	// Add score
	void AddScore(unsigned int dwScore);
	// Get score
	unsigned int GetScore();

private:
	// Score
    unsigned int m_dwScore;
};

#endif
