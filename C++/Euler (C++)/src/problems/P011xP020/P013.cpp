#include "../../base/problem.h"

#include <sstream>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

/**
 * P013<br>
 * Work out the first ten digits of the sum = sum of the following one-hundred 50-digit numbers.<br>
 * Ans: 5537376230
 */
class P013: public Problem
{
	public:
		P013()
		{
			problem_number = 13;
			variations = 3;
			size = 0;
			mag = 0;
		}
		~P013()
		{
		}

		std::string execute(int variation)
		{
			switch (variation)
			{
				case 0:
					return to_string(bruteForce());
				case 1:
					return "-1";
				case 2:
				case -1:
					return to_string(faster());
				default:
					return std::string("unavailable");
			}
			return NULL;
		}

	private:

		/**
		 * We have 50 digit numbers, so just add from right to left, carrying over and storing
		 * the result in an array
		 * @return
		 */
		std::string bruteForce()
		{
			std::string input = makeString();

			std::vector<int> *answer = new std::vector<int>();
			int carry = 0;
			for (int ii = 49; ii >= 0; ii--)
			{
				// add our carry-over into the list of numbers we'll add
				int ans = carry;
				for (int jj = 0; jj < 100; jj++)
				{
					// find our individual digits in the columns and add them
					int n = input[jj * 50 + ii] - '0';
					ans += n;
				}
				// add the one's digit to our answer
				answer->push_back(ans % 10);
				// compute the carry-over
				carry = ans / 10;
			}
			while (carry > 0)
			{
				answer->push_back(carry % 10);
				carry = carry / 10;
			}

			std::ostringstream oss;
			std::string retVal = "";
			for (unsigned int ii = answer->size() - 1; ii > answer->size() - 11; ii--)
			{
				oss << answer->at(ii);
				retVal += to_string(answer->at(ii));
			}

			return retVal;
		}

		int size; // size of our ulong arrays
		int mag;  // magnitude of our ulongs

		/**
		 * Try using larger amounts of storage to do the addition.
		 */
		std::string faster()
		{
			std::string input = makeString();

			// get the magnitude of the largest unsigned long
			unsigned long max = ULONG_MAX;

			// addition will never have more than a single carry bit, so chop off the max digit and find
			// the magnitude of the max ULONG for this architecture
			mag = 0;
			while (max > 0)
			{
				max /= 10;
				mag++;
			}
			mag -= 1; // subtract one to provide a carry

			// how many do we need for a digit of length 50 plus the max overflow of 9*100 (two more digits)
			size = ceil(52.0 / mag);

			// initialize our sum
			std::vector<unsigned long> sum;
			for (int ii = 0; ii < size; ii++)
			{
				sum.push_back(0);
			}
			// there's 100 numbers to add, so we can get them in arrays of unsigned longs
			for (int ii = 0; ii < 100; ii++)
			{
				getAndAddULong(&input, ii * 50, sum);
			}

			// figure out the magnitude of the first element in the sum array
			unsigned long num = sum.at(0);
			int mag2 = 0;
			while (num > 0)
			{
				num /= 10;
				mag2++;
			}

			std::string answer;
			if (mag2 >= 10)
			{
				// we need the first ten digits
				answer = to_string(sum.at(0)).substr(0, 10);
			} else
			{
				answer = to_string(sum.at(0)) + to_string(sum.at(1)).substr(0, 10 - mag2);
			}

			return answer;
		}

		void getAndAddULong(std::string* input, int idx, std::vector<unsigned long> &sum)
		{
			// get 50 characters from the string starting at the index
			for (int ii = 0; ii < size; ii++)
			{
				int beg = 50 - (size - ii) * mag;
				int len = mag;
				if (beg < 0) // non even division for first element
				{
					len += beg;
					beg = 0;
				}
				std::string sub = input->substr(beg + idx, len);
				unsigned long ulong = strtoul(sub.c_str(), NULL, 0);
				sum.at(ii) = ulong + sum.at(ii);
			}

			// get the max power of ten since 10^mag results in a double, which overflows
			unsigned long pow = 10;
			for (int ii = 0; ii < mag - 1; ii++)
			{
				pow *= 10;
			}

			// now check the carry bits
			for (int ii = size - 1; ii > 0; ii--)
			{
				unsigned long carry = sum.at(ii) / pow;
				if (carry > 0)
					sum.at(ii - 1) = carry + sum.at(ii - 1);
			}
		}

		std::string makeString()
		{
			std::string input = std::string("37107287533902102798797998220837590246510135740250")
					+ std::string("46376937677490009712648124896970078050417018260538")
					+ std::string("74324986199524741059474233309513058123726617309629")
					+ std::string("91942213363574161572522430563301811072406154908250")
					+ std::string("23067588207539346171171980310421047513778063246676")
					+ std::string("89261670696623633820136378418383684178734361726757")
					+ std::string("28112879812849979408065481931592621691275889832738")
					+ std::string("44274228917432520321923589422876796487670272189318")
					+ std::string("47451445736001306439091167216856844588711603153276")
					+ std::string("70386486105843025439939619828917593665686757934951")
					+ std::string("62176457141856560629502157223196586755079324193331")
					+ std::string("64906352462741904929101432445813822663347944758178")
					+ std::string("92575867718337217661963751590579239728245598838407")
					+ std::string("58203565325359399008402633568948830189458628227828")
					+ std::string("80181199384826282014278194139940567587151170094390")
					+ std::string("35398664372827112653829987240784473053190104293586")
					+ std::string("86515506006295864861532075273371959191420517255829")
					+ std::string("71693888707715466499115593487603532921714970056938")
					+ std::string("54370070576826684624621495650076471787294438377604")
					+ std::string("53282654108756828443191190634694037855217779295145")
					+ std::string("36123272525000296071075082563815656710885258350721")
					+ std::string("45876576172410976447339110607218265236877223636045")
					+ std::string("17423706905851860660448207621209813287860733969412")
					+ std::string("81142660418086830619328460811191061556940512689692")
					+ std::string("51934325451728388641918047049293215058642563049483")
					+ std::string("62467221648435076201727918039944693004732956340691")
					+ std::string("15732444386908125794514089057706229429197107928209")
					+ std::string("55037687525678773091862540744969844508330393682126")
					+ std::string("18336384825330154686196124348767681297534375946515")
					+ std::string("80386287592878490201521685554828717201219257766954")
					+ std::string("78182833757993103614740356856449095527097864797581")
					+ std::string("16726320100436897842553539920931837441497806860984")
					+ std::string("48403098129077791799088218795327364475675590848030")
					+ std::string("87086987551392711854517078544161852424320693150332")
					+ std::string("59959406895756536782107074926966537676326235447210")
					+ std::string("69793950679652694742597709739166693763042633987085")
					+ std::string("41052684708299085211399427365734116182760315001271")
					+ std::string("65378607361501080857009149939512557028198746004375")
					+ std::string("35829035317434717326932123578154982629742552737307")
					+ std::string("94953759765105305946966067683156574377167401875275")
					+ std::string("88902802571733229619176668713819931811048770190271")
					+ std::string("25267680276078003013678680992525463401061632866526")
					+ std::string("36270218540497705585629946580636237993140746255962")
					+ std::string("24074486908231174977792365466257246923322810917141")
					+ std::string("91430288197103288597806669760892938638285025333403")
					+ std::string("34413065578016127815921815005561868836468420090470")
					+ std::string("23053081172816430487623791969842487255036638784583")
					+ std::string("11487696932154902810424020138335124462181441773470")
					+ std::string("63783299490636259666498587618221225225512486764533")
					+ std::string("67720186971698544312419572409913959008952310058822")
					+ std::string("95548255300263520781532296796249481641953868218774")
					+ std::string("76085327132285723110424803456124867697064507995236")
					+ std::string("37774242535411291684276865538926205024910326572967")
					+ std::string("23701913275725675285653248258265463092207058596522")
					+ std::string("29798860272258331913126375147341994889534765745501")
					+ std::string("18495701454879288984856827726077713721403798879715")
					+ std::string("38298203783031473527721580348144513491373226651381")
					+ std::string("34829543829199918180278916522431027392251122869539")
					+ std::string("40957953066405232632538044100059654939159879593635")
					+ std::string("29746152185502371307642255121183693803580388584903")
					+ std::string("41698116222072977186158236678424689157993532961922")
					+ std::string("62467957194401269043877107275048102390895523597457")
					+ std::string("23189706772547915061505504953922979530901129967519")
					+ std::string("86188088225875314529584099251203829009407770775672")
					+ std::string("11306739708304724483816533873502340845647058077308")
					+ std::string("82959174767140363198008187129011875491310547126581")
					+ std::string("97623331044818386269515456334926366572897563400500")
					+ std::string("42846280183517070527831839425882145521227251250327")
					+ std::string("55121603546981200581762165212827652751691296897789")
					+ std::string("32238195734329339946437501907836945765883352399886")
					+ std::string("75506164965184775180738168837861091527357929701337")
					+ std::string("62177842752192623401942399639168044983993173312731")
					+ std::string("32924185707147349566916674687634660915035914677504")
					+ std::string("99518671430235219628894890102423325116913619626622")
					+ std::string("73267460800591547471830798392868535206946944540724")
					+ std::string("76841822524674417161514036427982273348055556214818")
					+ std::string("97142617910342598647204516893989422179826088076852")
					+ std::string("87783646182799346313767754307809363333018982642090")
					+ std::string("10848802521674670883215120185883543223812876952786")
					+ std::string("71329612474782464538636993009049310363619763878039")
					+ std::string("62184073572399794223406235393808339651327408011116")
					+ std::string("66627891981488087797941876876144230030984490851411")
					+ std::string("60661826293682836764744779239180335110989069790714")
					+ std::string("85786944089552990653640447425576083659976645795096")
					+ std::string("66024396409905389607120198219976047599490197230297")
					+ std::string("64913982680032973156037120041377903785566085089252")
					+ std::string("16730939319872750275468906903707539413042652315011")
					+ std::string("94809377245048795150954100921645863754710598436791")
					+ std::string("78639167021187492431995700641917969777599028300699")
					+ std::string("15368713711936614952811305876380278410754449733078")
					+ std::string("40789923115535562561142322423255033685442488917353")
					+ std::string("44889911501440648020369068063960672322193204149535")
					+ std::string("41503128880339536053299340368006977710650566631954")
					+ std::string("81234880673210146739058568557934581403627822703280")
					+ std::string("82616570773948327592232845941706525094512325230608")
					+ std::string("22918802058777319719839450180888072429661980811197")
					+ std::string("77158542502016545090413245809786882778948721859617")
					+ std::string("72107838435069186155435662884062257473692284509516")
					+ std::string("20849603980134001723930671666823555245252804609722")
					+ std::string("53503534226472524250874054075591789781264330331690");

			return input;
		}
};
