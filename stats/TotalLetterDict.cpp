#include "LetterDict.hpp"

class TotalLetterDict: public LetterDict {
	public:
		static TotalLetterDict from_words(std::vector<std::string> words) {
			TotalLetterDict tld = TotalLetterDict();
			for (auto & word : words) {
				for (auto letter : word) {
					tld.inc(letter);
				}
			}
			return tld;
		}
};
