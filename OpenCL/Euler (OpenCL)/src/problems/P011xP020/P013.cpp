#include "../../base/problem.h"

class P013: public Problem
{
	/**
	 * P013<br>
	 * Work out the first ten digits of the sum = sum of the following one-hundred 50-digit numbers.<br>
	 * Ans: 5537376230
	 */
	public:
		P013()
		{
			problem_number = 13;
			variations = 2;
		}
		~P013() {}

		bool setup(int variation)
		{
			bool retval = false;
			cl = new CLKernel(kernelsize);
			switch (variation)
			{
				case 0:
					retval = brute_setup();
					break;
				case 1:
				case -1:
					retval = opt_setup();
					break;
				default:
					retval = false;
			}
			return retval;
		}

		bool teardown(int variation)
		{
			bool retval = false;
			switch (variation)
			{
				case 0:
					retval = brute_teardown();
					break;
				case 1:
				case -1:
					retval =opt_teardown();
					break;
				default:
					retval = false;
			}
			cl->releaseKernel();
			return retval;
		}

		void execute(int variation)
		{
			switch (variation)
			{
				case 0:
					brute();
					break;
				case 1:
				case -1:
					optimized();
					break;
				default:
					std::cout << "NOOP!" << std::endl;
					break;
			}
		}

	private:

		int size;
		cl_mem digits_mem;

		/**
		 * Brute force version
		 * load it all up, add with carry-over to a final area. Final array will be no bigger
		 * than 4 digits to replace the max digit (50*100 is 5000, 3 extra digits beyond original)
		 */
		bool brute_setup()
		{
			size = 50;
			int initialVal[50] = { 0 };
			int nums[5000];
			makeString(nums);

			cl->init("src/problems/P011xP020/P013.cl","brute");
         cl->createReadWriteMemory(sizeof(int)*50,&answer_mem);
         cl->createReadOnlyMemory(sizeof(int)*5000,&digits_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*50,&answer_mem,initialVal);
			cl->transferCPUObjectToGPU(sizeof(int)*5000,&digits_mem,nums);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &digits_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool brute_teardown()
		{
			int ans[50];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*50, &answer_mem, ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			std::string ansStr = "";
			int idx = 0;
			while (ansStr.length() < 10)
				ansStr += to_string(ans[idx++]);
			answer = to_string(ansStr);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(digits_mem);
			return true;
		}

		int brute()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		/**
		 * Try to do the same thing, but in a base of 10M rather than 10
		 */
		bool opt_setup()
		{
			size = 8;
			int initialVal[8] = { 0 };
			int nums[800]; // 100 8 digit numbers
			makeString2(nums);

			cl->init("src/problems/P011xP020/P013.cl","optimized");
			cl->createReadWriteMemory(sizeof(int)*8,&answer_mem);
			cl->createReadOnlyMemory(sizeof(int)*800,&digits_mem);
			cl->transferCPUObjectToGPU(sizeof(int)*8,&answer_mem,initialVal);
			cl->transferCPUObjectToGPU(sizeof(int)*800,&digits_mem,nums);
			cl->setupOpenCLKernelArgs(3,
					sizeof(cl_mem), &answer_mem,
					sizeof(cl_mem), &digits_mem,
					sizeof(int), &size);
			cl->waitForQueue(); // sync
			setThreads(size);
			return true;
		}

		bool opt_teardown()
		{
			int ans[8];
			if (!cl->transferGPUObjectToCPU(sizeof(int)*8, &answer_mem, ans))
			{
				std::cout << "ERROR:: Could not read answer from GPU!" << std::endl;
				return false;
			}
			std::string ansStr = "";
			int idx = 0;
			while (ansStr.length() < 10)
				ansStr += to_string(ans[idx++]);
			answer = to_string(ansStr);
			clReleaseMemObject(answer_mem);
			clReleaseMemObject(digits_mem);
			return true;
		}

		int optimized()
		{
			cl->launchKernel(threadsize);
			cl->waitForQueue();
			return 0;
		}

		std::string getString()
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

		void makeString(int* nums)
		{
			std::string str = getString();
			for (int ii = 0; ii < 5000; ii++)
			{
				nums[ii] = str.at(ii) - '0';
			}
		}

		void makeString2(int* nums)
		{
			std::string str = getString();

			for (int ii = 0; ii < 100; ii++)
			{
				// want this to be divisible by 7, so we need 56 numbers
				nums[8*ii] = str.at(50*ii) - '0'; // six zeros plus the 7th digit
				for (int jj = 0; jj < 7; jj++)
				{
					nums[8*ii+1+jj] = 0;
					int tens = 1000000;
					for (int kk = 0; kk < 7; kk++)
					{
						nums[8*ii+1+jj] += (str.at(50*ii + 1 + 7*jj + kk) - '0')*tens;
						tens = tens / 10;
					}
				}
			}
		}
};
