#include "stscore.h"

// Constructor
CStScore::CStScore()
{
    // Clear
    Clear();
}

// Clear
void CStScore::Clear()
{
	m_dwScore = 0;
}

// Add score
void CStScore::AddScore(unsigned int dwScore)
{
	m_dwScore += dwScore;
}

// Get score
unsigned int CStScore::GetScore()
{
	return m_dwScore;
}
