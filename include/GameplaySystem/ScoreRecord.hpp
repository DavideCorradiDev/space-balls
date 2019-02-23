#ifndef SCORERECORD_HPP
#define SCORERECORD_HPP

#include <string>
#include <vector>

namespace mnk {

class ScoreRecord {
public:
    struct ScoreEntry {
        ScoreEntry();
        ScoreEntry(const std::string& name, unsigned int score);
        std::string name;
        unsigned int score;
    };

public:
    ScoreRecord();
    ScoreRecord(std::size_t maxScoreEntries);

    void addEntry(const ScoreEntry& entry);
    void print() const;
    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;
    std::size_t getNumberOfEntries() const;
    const ScoreEntry& operator[](std::size_t idx) const;
    std::size_t getMaxScoreEntries() const;
    void setMaxScoreEntries(std::size_t value);

private:
    std::vector<ScoreEntry> mEntries;
    std::size_t mMaxScoreEntries;
};

}

#endif // SCORERECORD_HPP
