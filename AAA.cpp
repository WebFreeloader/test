#undef UNICODE
#undef _UNICODE
#include <conio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <graphics.h>		// 引用图形库头文件
#define PI 3.14159265359
using namespace std;
struct cards
{
	int color;
	int num;
	IMAGE img;
};
struct player
{
	int age = 0;
	int money = 0;
	string name = "NULL";
	string sex = "NULL";
	string character = "NULL";
	string fame = "NULL";
	cards poker1;
	cards poker2;
	cards poker3;
	player* next;
	bool isSeen;
	bool isGivenUp;
};
void DataBaseRoll(string& name, string& sex, string& character);
void initPlayer(player& a);
void save();
void load();
void shuffle(player& player1, player& player2);
void initPoker();
void initGraph();
void initRules1();
void initRules2();
void initHostSet();
void HostReview();
void fameJudge(player& a);
void initQuestion();
void loadGame();
void gamesGoing();
void displayCards(player a, int num);
void playingGames(player& a, player& b);
int calcValue(player& a);
int cardCompare(player& a, player& b);
int actionJudge(player& a, player& b, player& c, int turns, int playerLeft);
FILE* mem;
player host;
int hostmoney;
int evymoney;
int playernum;
int player1money;
int player2money;
int main()
{
	srand(time(0));
	load();
	//initPoker();
	player host;
	initgraph(1000, 600);
	initGraph();
}
void initGraph()
{
	IMAGE img1;
	hostmoney = 0;
	evymoney = host.money / 100;
	playernum = 3;
	host.isSeen = 0;
	host.isGivenUp = 0;
	player1money = 0;
	player2money = 0;
	loadimage(&img1, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\background.jpg");
	putimage(0, 0, &img1);
	Resize(&img1, 700, 600);
	IMAGE img2;
	loadimage(&img2, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\cover.png");
	putimage(70, 50, &img2);
	line(700, 0, 700, 600);
	setfillcolor(BLACK);
	solidrectangle(700, 0, 1000, 600);
	rectangle(760, 120, 940, 160);
	rectangle(760, 240, 940, 280);
	rectangle(760, 360, 940, 400);
	rectangle(760, 480, 940, 520);
	RECT r1 = { 760, 120, 940, 160 };
	RECT r2 = { 760, 240, 940, 280 };
	RECT r3 = { 760, 360, 940, 400 };
	RECT r4 = { 760,480,940,520 };
	RECT r5 = { 700,500,1000,600 };
	char s[] = "温馨提示：禁止赌博，本游戏仅供娱乐。";
	drawtext("创建角色", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("继续游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("规则", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("退出", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s, &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;
	while (TRUE)
	{
		m = getmessage(EM_MOUSE);
		if (m.x <= 940 && m.x >= 760 && m.y <= 400 && m.y >= 360 && m.message == WM_LBUTTONDOWN)
			initRules1();
		if (m.x <= 940 && m.x >= 760 && m.y <= 520 && m.y >= 480 && m.message == WM_LBUTTONDOWN)
		{
			save();
			closegraph();
		}
		if (m.x <= 940 && m.x >= 760 && m.y <= 160 && m.y >= 120 && m.message == WM_LBUTTONDOWN)
		{
			initQuestion();
			initHostSet();
		}
		if (m.x <= 940 && m.x >= 760 && m.y <= 280 && m.y >= 240 && m.message == WM_LBUTTONDOWN)
		{
			HostReview();
		}
	}
}
void save()
{
	mem = fopen("memory.txt", "w+");
	fwrite(&host.name, sizeof(host.name), 1, mem);
	fwrite(&host.age, sizeof(host.age), 1, mem);
	fwrite(&host.money, sizeof(host.money), 1, mem);
	fwrite(&host.character, sizeof(host.character), 1, mem);
	fwrite(&host.sex, sizeof(host.sex), 1, mem);
	fwrite(&host.fame, sizeof(host.fame), 1, mem);
	fclose(mem);
}
void load()
{
	mem = fopen("memory.txt", "r");
	fread(&host.name, sizeof(host.name), 1, mem);
	fread(&host.age, sizeof(host.age), 1, mem);
	fread(&host.money, sizeof(host.money), 1, mem);
	fread(&host.character, sizeof(host.character), 1, mem);
	fread(&host.sex, sizeof(host.sex), 1, mem);
	fread(&host.fame, sizeof(host.fame), 1, mem);
	fclose(mem);
}
void initRules1()
{
	solidrectangle(700, 0, 1000, 600);
	RECT r1 = { 700, 0, 1000, 600 };
	RECT r2 = { 730,520,830,570 };
	RECT r3 = { 870,520,970,570 };
	char s[] = "      欢迎来到属于你自己的赌王之路，在这一路上你会遇到各种各样的对手，动用智慧，使用各种手段在游戏中胜出，赢光他们的钱，成为赌王吧!\n\n游戏的规则很有趣，如下：\n      一副牌(52张无大小王)，从庄家开始发牌，第一次开局的话，随机选择一个用户为庄家先发牌。每人发三张牌，牌面向下，为暗牌。庄家逆时针的下一家先开始下注，其他玩家依次逆时针操作。轮到玩家操作时，玩家根据条件和判断形势可以进行加、跟、看牌、放弃、比牌等操作。最后一名玩家胜利，获得当前所有的下注。\n\n游戏流程：\n\n      1、投入底注：发牌之前大家先付出一定的游戏分作为底注。\n\n      2、发牌：一副牌（52张无大小王），从庄家开始发牌，第一次开局的话，随机选择一个用户为庄家先发牌。每人发三张牌，牌面向下，为暗牌。\n\n      3、游戏人数为3人。庄家逆时针的下一家先开始下注，其他玩家依次逆时针操作。轮到玩家操作时，玩家根据条件和判断形势可以进行加、跟、看牌、放弃、比牌等操作。\n\n";
	char s2[] = "下一页";
	char s3[] = "返回";
	rectangle(730, 520, 830, 570);
	rectangle(870, 520, 970, 570);
	drawtext(s, &r1, DT_TOP | DT_WORDBREAK);
	drawtext(s2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s3, &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;
	while (TRUE)
	{
		m = getmessage(EM_MOUSE);
		if (m.x <= 970 && m.x >= 870 && m.y <= 570 && m.y >= 520 && m.message == WM_LBUTTONDOWN)
		{
			initGraph();
			break;
		}
		if (m.x <= 830 && m.x >= 730 && m.y <= 570 && m.y >= 520 && m.message == WM_LBUTTONDOWN)
		{
			initRules2();
			break;
		}
	}
}
void initRules2()
{
	solidrectangle(700, 0, 1000, 600);
	RECT r1 = { 700, 0, 1000, 600 };
	RECT r2 = { 730,520,830,570 };
	RECT r3 = { 870,520,970,570 };
	char s1[] = "4、看牌\na. 从第二轮开始，玩家可以选择看牌，不看，或者放弃。没有选择放弃的玩家，轮到自己动作时，可以选择看自己的牌，在看牌后再选择是否跟、加，或比牌，如果看过了牌，跟注和加注则需付底注的双倍分，如果不看牌，暗牌操作，跟注加注则只需要付与底注等同的分。\nb. 游戏中放弃的玩家，在结束游戏前无权查看自己的牌和其他玩家的牌。\nc. 游戏结束后，将公开全部玩家的牌！\n\n5、比牌\na. 从第二轮开始，玩家可以投注，或者选择支付当前投注的双倍游戏分与另外一名未放弃玩家比牌。比输的玩家视为自动放弃。\nb. 比牌双方进行比牌，所有玩家看不到两人的牌面。\nc. 牌型牌点相同时被比牌方胜。\n\n6、胜负判定\na. 豹子(三张点数相同)>同花顺(花色相同的顺子)>金花(花色相同的三张牌)>顺子(三张点数相连)>对子(两张点数相同)>单张。\nb. 当豹子存在时，花色不同235>豹子。\nc. AKQ >KQJ>...234。单牌大小：A>K>Q..>2。\nd. 对子的情况，先比对，再比单。\ne. 全部为单张时，比较最大的单张,若相同,往后顺延\nf. 比牌牌型等大，先开为负。";
	char s2[] = "上一页";
	char s3[] = "返回";
	rectangle(730, 520, 830, 570);
	rectangle(870, 520, 970, 570);
	drawtext(s1, &r1, DT_WORDBREAK);
	drawtext(s2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s3, &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;
	while (TRUE)
	{
		m = getmessage(EM_MOUSE);
		if (m.x <= 970 && m.x >= 870 && m.y <= 570 && m.y >= 520 && m.message == WM_LBUTTONDOWN)
		{
			initGraph();
			break;
		}
		if (m.x <= 830 && m.x >= 730 && m.y <= 570 && m.y >= 520 && m.message == WM_LBUTTONDOWN)
		{
			initRules1();
			break;
		}
	}
}
void initQuestion()
{
	solidrectangle(700, 0, 1000, 600);
	outtextxy(700, 50, "创建新角色可能会覆盖您原有的角色");
	outtextxy(700, 70, "是否确认？");
	rectangle(800, 100, 860, 130);
	rectangle(880, 100, 940, 130);
	RECT r1 = { 800, 100, 860, 130 };
	RECT r2 = { 880, 100, 940, 130 };
	drawtext("返回", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("确认", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;
	while (TRUE)
	{
		m = getmessage();
		if (m.x <= 860 && m.x >= 800 && m.y <= 130 && m.y >= 100 && m.message == WM_LBUTTONDOWN)
		{
			initGraph();
		}
		if (m.x <= 940 && m.x >= 880 && m.y <= 130 && m.y >= 100 && m.message == WM_LBUTTONDOWN)
		{
			initHostSet();
		}
	}
}
void creatIdent()
{
	solidrectangle(700, 0, 1000, 600);
	outtextxy(700, 10, "从身无分文，变成腰缠万贯吧！");
	outtextxy(700, 50, "结束游戏请务必从主界面点击退出键退出");
	outtextxy(700, 70, "否则将无法正常进行存档！");
	RECT r = { 700, 100, 1000, 600 };
	initPlayer(host); host.money = 1000;
	string s = "你叫做" + host.name + "," + host.sex + "性,今年" + to_string(host.age) + "岁,从小到大人们都说你是一个" + host.character + "的人，可惜天有不测风云，一场变故使你失去了所有，只剩下了" + to_string(host.money) + "元钱，你励志从现在的穷困潦倒变成腰缠万贯的赌王，于是你走上了这条道路。你的故事，才刚刚开始。。。";
	drawtext(s.c_str(), &r, DT_WORDBREAK);
	rectangle(790, 200, 860, 230);
	rectangle(880, 200, 940, 230);
	RECT r1 = { 790, 200, 860, 230 };
	RECT r2 = { 880, 200, 940, 230 };
	drawtext("更换身份", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("确认", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void initHostSet()
{
	creatIdent();
	ExMessage m;
	while (TRUE)
	{
		m = getmessage();
		if (m.x <= 860 && m.x >= 800 && m.y <= 230 && m.y >= 200 && m.message == WM_LBUTTONDOWN)
		{
			creatIdent();
		}
		if (m.x <= 940 && m.x >= 880 && m.y <= 230 && m.y >= 200 && m.message == WM_LBUTTONDOWN)
		{
			initGraph();
		}
	}
}
void HostReview()
{
	solidrectangle(700, 0, 1000, 600);
	if (host.name == "NULL")
	{
		outtextxy(700, 50, "您还没有创建角色，请前往创建新角色");
		RECT r1 = { 800, 100, 860, 130 };
		rectangle(800, 100, 860, 130);
		drawtext("返回", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		ExMessage m;
		while (TRUE)
		{
			m = getmessage();
			if (m.x <= 860 && m.x >= 800 && m.y <= 130 && m.y >= 100 && m.message == WM_LBUTTONDOWN)
			{
				initGraph();
			}
		}
	}
	else
	{
		string s = "你的名字：   " + host.name;
		outtextxy(700, 100, s.c_str());
		s = "你的年龄：   " + to_string(host.age);
		outtextxy(700, 120, s.c_str());
		s = "你的性格：   " + host.character;
		outtextxy(700, 140, s.c_str());
		s = "你的资产：   " + to_string(host.money);
		outtextxy(700, 160, s.c_str());
		fameJudge(host);
		s = "你的称号：   " + host.fame;
		outtextxy(700, 180, s.c_str());
		outtextxy(700, 220, "您确定以当前角色继续进行游戏吗？");
		rectangle(800, 260, 860, 290);
		rectangle(880, 260, 940, 290);
		RECT r1 = { 800, 260, 860, 290 };
		RECT r2 = { 880, 260, 940, 290 };
		drawtext("返回", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("确认", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		ExMessage m;
		while (TRUE)
		{
			m = getmessage();
			if (m.x <= 860 && m.x >= 800 && m.y <= 290 && m.y >= 260 && m.message == WM_LBUTTONDOWN)
			{
				initGraph();
			}
			if (m.x <= 940 && m.x >= 880 && m.y <= 290 && m.y >= 260 && m.message == WM_LBUTTONDOWN)
			{
				loadGame();
			}
		}
	}
}
void loadGame()
{
	solidrectangle(700, 0, 1000, 600);
	line(700, 400, 1000, 400);
	string s = "姓名：  " + host.name;
	outtextxy(705, 405, s.c_str());
	s = "年龄：  " + to_string(host.age) + "岁";
	outtextxy(825, 405, s.c_str());
	s = "性别：  " + host.sex;
	outtextxy(705, 445, s.c_str());
	s = "资产：  " + to_string(host.money) + "元";
	outtextxy(825, 445, s.c_str());
	s = "性格：  " + host.character;
	outtextxy(705, 485, s.c_str());
	s = "称号：  " + host.fame;
	outtextxy(825, 485, s.c_str());
	rectangle(790, 550, 860, 580);
	rectangle(880, 550, 940, 580);
	RECT r1 = { 790, 550, 860, 580 };
	RECT r2 = { 880, 550, 940, 580 };
	drawtext("开始对局", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("返回", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;
	while (TRUE)
	{
		m = getmessage();
		if (m.x <= 940 && m.x >= 880 && m.y <= 580 && m.y >= 550 && m.message == WM_LBUTTONDOWN)
			HostReview();
		if (m.x <= 860 && m.x >= 790 && m.y <= 580 && m.y >= 550 && m.message == WM_LBUTTONDOWN)
			gamesGoing();
	}
}
void gamesGoing()
{
	solidrectangle(790, 550, 860, 580);
	IMAGE img1;
	loadimage(&img1, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\gameground.jpg");
	ExMessage m;
	putimage(0, 0, &img1);
	if (host.money < 100)
	{
		solidrectangle(790, 550, 860, 580);
		while (TRUE)
		{
			outtextxy(700, 100, "您已身无分文，请从头再来。");
			solidrectangle(880, 550, 940, 580);
			rectangle(880, 150, 940, 180);
			RECT r2 = { 880, 150, 940, 180 };
			drawtext("返回", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			m = getmessage();
			if (m.x <= 940 && m.x >= 880 && m.y <= 180 && m.y >= 150 && m.message == WM_LBUTTONDOWN)
				initGraph();
		}
	}
	IMAGE img2;
	loadimage(&img2, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\0.png");
	putimage(325, 250, &img2);
	player player1, player2;
	initPlayer(player1);
	initPlayer(player2);
	RECT r = { 700,0,1000,600 };
	string s = "您的对手是" + player1.name + "和" + player2.name + "。";
	outtextxy(700, 0, s.c_str());
	s = player1.name + ",性别" + player1.sex + ",今年" + to_string(player1.age) + "岁,资产" + to_string(player1.money) + "元";
	outtextxy(700, 20, s.c_str());
	s = "性格" + player1.character + ",身边人都称其为" + player1.fame;
	outtextxy(700, 40, s.c_str());
	s = player2.name + ",性别" + player2.sex + ",今年" + to_string(player2.age) + "岁,资产" + to_string(player2.money) + "元";
	outtextxy(700, 60, s.c_str());
	s = "性格" + player2.character + ",身边人都称其为" + player2.fame;
	outtextxy(700, 80, s.c_str());
	outtextxy(700, 100, "逃跑会扣除一定资产且需要把当轮决策做完");
	outtextxy(700, 120, "点击中间扑克牌开牌！");
	while (TRUE)
	{
		m = getmessage();
		if (m.x <= 940 && m.x >= 880 && m.y <= 580 && m.y >= 550 && m.message == WM_LBUTTONDOWN)
		{
			IMAGE img1;
			loadimage(&img1, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\gameground.jpg");
			putimage(0, 0, &img1);
			loadGame();
		}
		if (m.x <= 396 && m.x >= 325 && m.y <= 346 && m.y >= 250 && m.message == WM_LBUTTONDOWN)
		{
			playingGames(player1, player2);
			break;
		}
	}
}
void playingGames(player& player1, player& player2)
{
	IMAGE img1, img2, img3;
	loadimage(&img1, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\00.png");
	loadimage(&img2, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\0.png");
	loadimage(&img3, "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\gameground.jpg");
	int tmp = rand() % 3;
	player* head = NULL;
	host.next = &player1;
	player1.next = &player2;
	player2.next = &host;
	for (int times = 1; times <= 10; times++)
	{
		host.isSeen = 0;
		host.isGivenUp = 0;
		player1.isSeen = 0;
		player1.isGivenUp = 0;
		player2.isSeen = 0;
		player2.isGivenUp = 0;
		hostmoney = 0;
		player1money = 0;
		player2money = 0;
		playernum = 3;
		fameJudge(host);
		putimage(0, 0, &img3);
		putimage(325, 250, &img2);
		putimage(100, 240, &img1);
		putimage(100, 280, &img1);
		putimage(100, 320, &img1);
		putimage(525, 240, &img1);
		putimage(525, 280, &img1);
		putimage(525, 320, &img1);
		putimage(290, 420, &img2);
		putimage(330, 420, &img2);
		putimage(370, 420, &img2);
		solidrectangle(700, 0, 1000, 400);
		line(700, 400, 1000, 400);
		if (tmp == 0)
		{
			head = &host;
			string s = "您的位置是1号位";
			outtextxy(700, 0, s.c_str());
			s = player1.name + "的位置是2号位";
			outtextxy(700, 20, s.c_str());
			s = player2.name + "的位置是3号位 游戏开始";
			outtextxy(700, 40, s.c_str());
		}
		if (tmp == 1)
		{
			head = &player1;
			string s = "您的位置是3号位";
			outtextxy(700, 0, s.c_str());
			s = player1.name + "的位置是1号位";
			outtextxy(700, 20, s.c_str());
			s = player2.name + "的位置是2号位 游戏开始";
			outtextxy(700, 40, s.c_str());
		}
		if (tmp == 2)
		{
			head = &player2;
			string s = "您的位置是2号位";
			outtextxy(700, 0, s.c_str());
			s = player1.name + "的位置是3号位";
			outtextxy(700, 20, s.c_str());
			s = player2.name + "的位置是1号位 游戏开始";
			outtextxy(700, 40, s.c_str());
		}
		string s = player1.name + "   " + player1.character;
		setbkmode(TRANSPARENT);
		outtextxy(520, 180, s.c_str());
		s = "资产:  " + to_string(player1.money) + "元";
		outtextxy(520, 200, s.c_str());
		s = player2.name + "   " + player2.character;
		outtextxy(95, 180, s.c_str());
		s = "资产:  " + to_string(player2.money) + "元";
		outtextxy(95, 200, s.c_str());
		outtextxy(700, 60, "本局游戏共10盘，每盘游戏的底注是资产");
		outtextxy(700, 80, "最少玩家资产的百分之1取整");
		s = "最少的资产是" + to_string(min(min(player1.money, player2.money), host.money)) + "元，故底注为" + to_string(min(min(player1.money, player2.money), host.money) / 100) + "元";
		outtextxy(700, 100, s.c_str());
		outtextxy(700, 120, "左键点击中间牌堆进行加注/跟注");
		outtextxy(700, 140, "左键点击自己的牌进行看牌");
		outtextxy(700, 160, "右键点击自己的牌进行放弃");
		outtextxy(700, 180, "左键点击其他人的牌进行比牌");
		line(700, 200, 1000, 200);
		solidrectangle(880, 550, 940, 580);
		RECT r = { 880, 550, 940, 580 };
		rectangle(880, 550, 940, 580);
		evymoney = min(min(player1.money, player2.money), host.money) / 100;
		drawtext("逃跑", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		solidrectangle(820, 440, 1000, 500);
		s = "资产：  " + to_string(host.money) + "元";
		outtextxy(825, 445, s.c_str());
		s = "称号：  " + host.fame;
		outtextxy(825, 485, s.c_str());
		shuffle(player1, player2);
		ExMessage m;
		for (int turns = 1; turns <= 30; turns++)
		{
			solidrectangle(700, 200, 1000, 220);
			line(700, 200, 1000, 200);
			int y = 0;
			s = "第" + to_string(times) + "盘,  第" + to_string(turns) + "轮";
			outtextxy(800, 205, s.c_str());
			while (TRUE)
			{
				for (int i = 1; i <= 3; i++)
				{
					int sgn = 0;
					if (head == &host && sgn != 1)
					{
						sgn = 1;
						y += 20;
						if (host.isGivenUp == 0)
						{
							s = "等待您的决策......";
							outtextxy(705, 200 + y, s.c_str());
							while (TRUE)
							{
								m = getmessage();
								if (m.x <= 396 && m.x >= 325 && m.y <= 346 && m.y >= 250 && m.message == WM_LBUTTONDOWN)
								{
									if (host.isSeen == 0)
									{
										y += 20;
										s = "您选择加注(" + to_string(evymoney) + "元)";
										outtextxy(705, 200 + y, s.c_str());
										hostmoney += evymoney;
										head = head->next;
										break;
									}
									else
									{
										y += 20;
										s = "您选择加注(" + to_string(evymoney * 2) + "元)";
										outtextxy(705, 200 + y, s.c_str());
										hostmoney += evymoney * 2;
										head = head->next;
										break;
									}
								}
								if (m.x <= 466 && m.x >= 290 && m.y <= 491 && m.y >= 420 && m.message == WM_LBUTTONDOWN && turns != 1)
								{
									if (host.isSeen == 0)
									{
										i--;
										y += 20;
										host.isSeen = 1;
										s = "您选择看牌";
										outtextxy(705, 200 + y, s.c_str());
										displayCards(host, 1);
										break;
									}

								}
								if (m.x <= 466 && m.x >= 290 && m.y <= 491 && m.y >= 420 && m.message == WM_LBUTTONDOWN && turns == 1)
								{
									i--;
									y += 20;
									s = "当前为第一轮，无法看牌！";
									outtextxy(705, 200 + y, s.c_str());
									break;
								}
								if (m.x <= 466 && m.x >= 290 && m.y <= 491 && m.y >= 420 && m.message == WM_RBUTTONDOWN)
								{
									y += 20;
									s = "您选择本轮放弃！";
									host.isGivenUp = 1;
									head = head->next;
									playernum--;
									outtextxy(705, 200 + y, s.c_str());
									outtextxy(460, 460, "已放弃");
									break;
								}
								if (m.x <= 196 && m.x >= 100 && m.y <= 391 && m.y >= 240 && m.message == WM_LBUTTONDOWN && turns == 1)
								{
									i--;
									y += 20;
									s = "当前为第一轮，无法比牌！";
									outtextxy(705, 200 + y, s.c_str());
									break;
								}
								if (m.x <= 196 && m.x >= 100 && m.y <= 391 && m.y >= 240 && m.message == WM_LBUTTONDOWN && turns != 1 && (*(head->next->next)).isGivenUp == 0)
								{
									y += 20;
									if (host.isSeen == 0)
									{
										s = "您选择加注" + to_string(evymoney) + "元与" + (*(head->next->next)).name + "比牌";
										hostmoney += evymoney;
									}
									if (host.isSeen == 1)
									{
										s = "您选择加注" + to_string(2 * evymoney) + "元与" + (*(head->next->next)).name + "比牌";
										hostmoney += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									displayCards(*(head->next->next), 2);
									if (cardCompare(host, (*(head->next->next))) == 1)
									{
										y += 20;
										s = "您赢了," + (*(head->next->next)).name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(130, 400, "已放弃");
										playernum--;
										(*(head->next->next)).isGivenUp = 1;
										head = head->next;
										break;
									}
									if (cardCompare(host, (*(head->next->next))) <= 0)
									{
										y += 20;
										s = (*(head->next->next)).name + "赢了,您放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(460, 460, "已放弃");
										playernum--;
										host.isGivenUp = 1;
										head = head->next;
										break;
									}
								}
								if (m.x <= 621 && m.x >= 525 && m.y <= 391 && m.y >= 240 && m.message == WM_LBUTTONDOWN && turns == 1)
								{
									i--;
									y += 20;
									s = "当前为第一轮，无法比牌！";
									outtextxy(705, 200 + y, s.c_str());
									break;
								}
								if (m.x <= 621 && m.x >= 525 && m.y <= 391 && m.y >= 240 && m.message == WM_LBUTTONDOWN && turns != 1 && (*(head->next)).isGivenUp == 0)
								{
									y += 20;
									if (host.isSeen == 0)
									{
										s = "您选择加注" + to_string(evymoney) + "元与" + (*(head->next)).name + "比牌";
										hostmoney += evymoney;
									}
									if (host.isSeen == 1)
									{
										s = "您选择加注" + to_string(2 * evymoney) + "元与" + (*(head->next)).name + "比牌";
										hostmoney += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									displayCards(*(head->next), 3);
									if (cardCompare(host, (*(head->next))) == 1)
									{
										y += 20;
										s = "您赢了," + (*(head->next)).name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(540, 400, "已放弃");
										playernum--;
										(*(head->next)).isGivenUp = 1;
										head = head->next;
										break;
									}
									if (cardCompare(host, (*(head->next))) == 0)
									{
										y += 20;
										s = (*(head->next)).name + "赢了,您放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(460, 460, "已放弃");
										playernum--;
										host.isGivenUp = 1;
										head = head->next;
										break;
									}
								}
								if (y >= 160)
								{
									y = 20;
									solidrectangle(700, 220, 1000, 400);
									line(700, 400, 1000, 400);
								}
							}
						}
						else
						{
							s = "您已放弃!";
							outtextxy(705, 200 + y, s.c_str());
							head = head->next;
						}
					}
					if (head == &player1 && sgn != 1)
					{
						sgn = 1;
						int k = actionJudge(player1, player2, host, turns, playernum);
						if (player1.isGivenUp == 0)
						{
							if (k == 1 && player1.isSeen == 0)//加注跟注
							{
								k = 1;
								y += 20;
								s = player1.name + "选择加注(" + to_string(evymoney) + "元)";
								outtextxy(705, 200 + y, s.c_str());
								player1money += evymoney;
								head = head->next;
							}
							if (k == 1 && player1.isSeen == 1)
							{
								y += 20;
								s = player1.name + "选择加注(" + to_string(2 * evymoney) + "元)";
								outtextxy(705, 200 + y, s.c_str());
								player1money += 2 * evymoney;
								head = head->next;
							}
							if (k == 2)//看牌
							{
								i--;
								y += 20;
								player1.isSeen = 1;
								s = player1.name + "选择看牌";
								outtextxy(705, 200 + y, s.c_str());
							}
							if (k == 3)//放弃
							{
								y += 20;
								s = player1.name + "选择本轮放弃！";
								player1.isGivenUp = 1;
								playernum--;
								outtextxy(705, 200 + y, s.c_str());
								outtextxy(540, 400, "已放弃");
								head = head->next;
							}
							if (k == 4)//与下家比牌
							{
								y += 20;
								if (player2.isGivenUp == 0)
								{
									if (player1.isSeen == 0)
									{
										s = player1.name + "选择加注" + to_string(evymoney) + "元与" + player2.name + "比牌";
										player1money += evymoney;
									}
									if (player1.isSeen == 1)
									{
										s = player1.name + "选择加注" + to_string(2 * evymoney) + "元与" + player2.name + "比牌";
										player1money += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									if (cardCompare(player1, player2) == 1)
									{
										y += 20;
										s = player1.name + "赢了," + player2.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(130, 400, "已放弃");
										playernum--;
										player2.isGivenUp = 1;
										head = head->next;
									}
									if (cardCompare(player1, player2) <= 0)
									{
										y += 20;
										s = player2.name + "赢了," + player1.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(540, 400, "已放弃");
										playernum--;
										player1.isGivenUp = 1;
										head = head->next;
									}
								}
								else if (host.isGivenUp == 0)
								{
									if (player1.isSeen == 0)
									{
										s = player1.name + "选择加注" + to_string(evymoney) + "元与您比牌";
										player1money += evymoney;
									}
									if (player1.isSeen == 1)
									{
										s = player1.name + "选择加注" + to_string(2 * evymoney) + "元与您比牌";
										player1money += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									if (cardCompare(player1, host) == 1)
									{
										y += 20;
										s = player1.name + "赢了,您放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(460, 460, "已放弃");
										playernum--;
										host.isGivenUp = 1;
										head = head->next;
									}
									if (cardCompare(player1, host) <= 0)
									{
										y += 20;
										s = "您赢了," + player1.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(540, 400, "已放弃");
										playernum--;
										player1.isGivenUp = 1;
										head = head->next;
									}
								}
							}
						}
						else
						{
							y += 20;
							s = player1.name + "已放弃!";
							outtextxy(705, 200 + y, s.c_str());
							head = head->next;
						}
					}
					if (head == &player2 && sgn != 1)
					{
						sgn = 1;
						int k = actionJudge(player2, host, player1, turns, playernum);
						if (player2.isGivenUp == 0)
						{
							if (k == 1 && player2.isSeen == 0)//加注跟注
							{
								y += 20;
								s = player2.name + "选择加注(" + to_string(evymoney) + "元)";
								outtextxy(705, 200 + y, s.c_str());
								player2money += evymoney;
								head = head->next;
							}
							if (k == 1 && player2.isSeen == 1)
							{
								y += 20;
								s = player2.name + "选择加注(" + to_string(2 * evymoney) + "元)";
								outtextxy(705, 200 + y, s.c_str());
								player2money += 2 * evymoney;
								head = head->next;
							}
							if (k == 2)//看牌
							{
								i--;
								y += 20;
								player2.isSeen = 1;
								s = player2.name + "选择看牌";
								outtextxy(705, 200 + y, s.c_str());
							}
							if (k == 3)//放弃
							{
								y += 20;
								s = player2.name + "选择本轮放弃！";
								player2.isGivenUp = 1;
								playernum--;
								outtextxy(705, 200 + y, s.c_str());
								outtextxy(130, 400, "已放弃");
								head = head->next;
							}
							if (k == 4)//与下家比牌
							{
								y += 20;
								if (host.isGivenUp == 0)
								{
									if (player2.isSeen == 0)
									{
										s = player2.name + "选择加注" + to_string(evymoney) + "元与您比牌";
										player2money += evymoney;
									}
									if (player2.isSeen == 1)
									{
										s = player2.name + "选择加注" + to_string(2 * evymoney) + "元与您比牌";
										player2money += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									if (cardCompare(player2, host) == 1)
									{
										y += 20;
										s = player2.name + "赢了,您放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(460, 460, "已放弃");
										playernum--;
										host.isGivenUp = 1;
										head = head->next;
									}
									if (cardCompare(player2, host) <= 0)
									{
										y += 20;
										s = "您赢了," + player2.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(130, 400, "已放弃");
										playernum--;
										player2.isGivenUp = 1;
										head = head->next;
									}
								}
								else if (player1.isGivenUp == 0)
								{
									if (player2.isSeen == 0)
									{
										s = player2.name + "选择加注" + to_string(evymoney) + "元与" + player1.name + "比牌";
										player2money += evymoney;
									}
									if (player2.isSeen == 1)
									{
										s = player2.name + "选择加注" + to_string(2 * evymoney) + "元与" + player1.name + "比牌";
										player2money += 2 * evymoney;
									}
									outtextxy(705, 200 + y, s.c_str());
									if (cardCompare(player2, player1) == 1)
									{
										y += 20;
										s = player2.name + "赢了," + player1.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(540, 460, "已放弃");
										playernum--;
										player1.isGivenUp = 1;
										head = head->next;
									}
									if (cardCompare(player2, player1) <= 0)
									{
										y += 20;
										s = player1.name + "赢了," + player2.name + "放弃！";
										outtextxy(705, 200 + y, s.c_str());
										outtextxy(130, 400, "已放弃");
										playernum--;
										player2.isGivenUp = 1;
										head = head->next;
									}
								}
							}
						}
						else
						{
							y += 20;
							s = player2.name + "已放弃!";
							outtextxy(705, 200 + y, s.c_str());
							head = head->next;
						}
					}
					if (i == 3)
					{
						while (TRUE)
						{
							m = getmessage();
							y = 0;
							RECT r = { 880,350,940,380 };
							rectangle(880, 350, 940, 380);
							drawtext("下一轮", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							if (m.x <= 940 && m.x >= 880 && m.y <= 580 && m.y >= 550 && m.message == WM_LBUTTONDOWN)
							{
								solidrectangle(700, 0, 1000, 400);
								solidrectangle(880, 550, 940, 580);
								line(700, 400, 1000, 400);
								outtextxy(700, 100, "您已逃跑");
								outtextxy(700, 120, "扣除当前资产的百分之20作为处罚。");
								host.money = host.money * 4 / 5;
								fameJudge(host);
								rectangle(880, 150, 940, 180);
								RECT r2 = { 880, 150, 940, 180 };
								drawtext("返回", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								while (TRUE)
								{
									m = getmessage();
									if (m.x <= 940 && m.x >= 880 && m.y <= 180 && m.y >= 150 && m.message == WM_LBUTTONDOWN)
										initGraph();
								}
							}

							if (m.x <= 940 && m.x >= 880 && m.y <= 380 && m.y >= 350 && m.message == WM_LBUTTONDOWN)
							{
								solidrectangle(700, 200, 1000, 400);
								line(700, 200, 1000, 200);
								line(700, 400, 1000, 400);
								y = 0;
								s = "第" + to_string(times) + "盘,  第" + to_string(turns) + "轮";
								outtextxy(800, 205, s.c_str());
								break;
							}
						}
					}
				}
				break;
			}
			if (turns == 30 || playernum <= 1)
			{
				displayCards(host, 1);
				displayCards(player1, 3);
				displayCards(player2, 2);
				string s;
				ExMessage m;
				if (host.isGivenUp == 0)
				{
					solidrectangle(700, 220, 1000, 400);
					line(700, 400, 1000, 400);
					y += 20;
					s = "您赢了,获得本盘的全部奖金！";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = "本盘奖金共" + to_string(player1money + player2money) + "元";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = player1.name + "下注" + to_string(player1money) + "元," + player2.name + "下注" + to_string(player2money) + "元。";
					outtextxy(705, 200 + y, s.c_str());
					player1.money -= player1money;
					player2.money -= player2money;
					host.money = host.money + player1money + player2money;
				}
				if (player1.isGivenUp == 0)
				{
					solidrectangle(700, 220, 1000, 400);
					line(700, 400, 1000, 400);
					y += 20;
					s = player1.name + "赢了,获得本盘的全部奖金！";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = "本盘奖金共" + to_string(hostmoney + player2money) + "元";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = "您下注" + to_string(hostmoney) + "元," + player2.name + "下注" + to_string(player2money) + "元。";
					outtextxy(705, 200 + y, s.c_str());
					host.money -= hostmoney;
					player2.money -= player2money;
					player1.money = player1.money + hostmoney + player2money;
				}
				if (player2.isGivenUp == 0)
				{
					solidrectangle(700, 220, 1000, 400);
					line(700, 400, 1000, 400);
					y += 20;
					s = player2.name + "赢了,获得本盘的全部奖金！";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = "本盘奖金共" + to_string(hostmoney + player1money) + "元";
					outtextxy(705, 200 + y, s.c_str());
					y += 20;
					s = "您下注" + to_string(hostmoney) + "元," + player1.name + "下注" + to_string(player1money) + "元。";
					outtextxy(705, 200 + y, s.c_str());
					host.money -= hostmoney;
					player1.money -= player1money;
					player2.money = player2.money + hostmoney + player1money;
				}
				RECT r = { 880,350,940,380 };
				rectangle(880, 350, 940, 380);
				drawtext("下一盘", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				while (TRUE)
				{
					m = getmessage();
					if (m.x <= 940 && m.x >= 880 && m.y <= 380 && m.y >= 350 && m.message == WM_LBUTTONDOWN)
						break;
				}
				break;
			}
		}
		if (times == 10)
		{
			solidrectangle(700, 200, 1000, 400);
			line(700, 200, 1000, 200);
			line(700, 400, 1000, 400);
			outtextxy(705, 250, "本局游戏结束！");
			RECT r = { 880,350,940,380 };
			rectangle(880, 350, 940, 380);
			drawtext("下一局", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			while (TRUE)
			{
				m = getmessage();
				if (m.x <= 940 && m.x >= 880 && m.y <= 380 && m.y >= 350 && m.message == WM_LBUTTONDOWN)
					loadGame();
			}
		}
	}
}
int calcValue(player& a)
{
	if (a.poker1.num == a.poker2.num && a.poker2.num == a.poker3.num)
		return 6;
	if ((a.poker1.num == a.poker2.num && a.poker2.num != a.poker3.num) || (a.poker1.num == a.poker3.num && a.poker2.num != a.poker3.num) || (a.poker3.num == a.poker2.num && a.poker2.num != a.poker1.num))
		return 2;
	if (a.poker1.num != a.poker2.num && a.poker2.num != a.poker3.num)
	{
		if (a.poker1.color == a.poker2.color && a.poker2.color == a.poker3.color)
		{
			if (((a.poker1.num - a.poker2.num == 1) && (a.poker2.num - a.poker3.num == 1)) || ((a.poker1.num - a.poker3.num == 1) && (a.poker3.num - a.poker2.num == 1)) || ((a.poker2.num - a.poker1.num == 1) && (a.poker1.num - a.poker3.num == 1)) || ((a.poker2.num - a.poker3.num == 1) && (a.poker3.num - a.poker1.num == 1)) || ((a.poker3.num - a.poker1.num == 1) && (a.poker1.num - a.poker2.num == 1)) || ((a.poker3.num - a.poker2.num == 1) && (a.poker2.num - a.poker1.num == 1)))
				return 5;
			else
				return 4;
		}
		else
		{
			if (((a.poker1.num - a.poker2.num == 1) && (a.poker2.num - a.poker3.num == 1)) || ((a.poker1.num - a.poker3.num == 1) && (a.poker3.num - a.poker2.num == 1)) || ((a.poker2.num - a.poker1.num == 1) && (a.poker1.num - a.poker3.num == 1)) || ((a.poker2.num - a.poker3.num == 1) && (a.poker3.num - a.poker1.num == 1)) || ((a.poker3.num - a.poker1.num == 1) && (a.poker1.num - a.poker2.num == 1)) || ((a.poker3.num - a.poker2.num == 1) && (a.poker2.num - a.poker1.num == 1)))
				return 3;
			else
				return 1;
		}
	}
}
int cardCompare(player& a, player& b)
{
	if (calcValue(a) == 6 && calcValue(b) == 1)
	{
		int k[3];
		k[0] = b.poker1.num;
		k[1] = b.poker2.num;
		k[2] = b.poker3.num;
		sort(k, k + 3);
		if (k[0] == 2 && k[1] == 3 && k[2] == 5)
			return 0;
	}
	if (calcValue(a) == 1 && calcValue(b) == 6)
	{
		int k[3];
		k[0] = a.poker1.num;
		k[1] = a.poker2.num;
		k[2] = a.poker3.num;
		sort(k, k + 3);
		if (k[0] == 2 && k[1] == 3 && k[2] == 5)
			return 1;
	}
	if (calcValue(a) > calcValue(b))
		return 1;
	if (calcValue(a) < calcValue(b))
		return 0;
	if (calcValue(a) == calcValue(b))
	{
		if (calcValue(a) == 1 || calcValue(a) == 4)
		{
			int m[3];
			int n[3];
			m[0] = a.poker1.num;
			m[1] = a.poker2.num;
			m[2] = a.poker3.num;
			n[0] = b.poker1.num;
			n[1] = b.poker2.num;
			n[2] = b.poker3.num;
			sort(m, m + 3);
			sort(n, n + 3);
			for (int i = 2; i >= 0; i--)
			{
				if (m[i] > n[i])
					return 1;
				if (m[i] < n[i])
					return 0;
			}
			return -1;
		}
		if (calcValue(a) == 2)
		{
			int m = 0;
			int n = 0;
			int p = 0;
			int q = 0;
			if (a.poker1.num == a.poker2.num)
			{
				m = a.poker1.num;
				n = a.poker3.num;
			}
			if (a.poker1.num == a.poker3.num)
			{
				m = a.poker1.num;
				n = a.poker2.num;
			}
			if (a.poker2.num == a.poker3.num)
			{
				m = a.poker2.num;
				n = a.poker1.num;
			}
			if (b.poker1.num == b.poker2.num)
			{
				p = b.poker1.num;
				q = b.poker3.num;
			}
			if (a.poker1.num == a.poker3.num)
			{
				p = b.poker1.num;
				q = b.poker2.num;
			}
			if (a.poker2.num == a.poker3.num)
			{
				p = b.poker2.num;
				q = b.poker1.num;
			}
			if (m > p)
				return 1;
			if (m < p)
				return 0;
			if (n > q)
				return 1;
			if (n < q)
				return 0;
			if (n == q)
				return -1;
		}
		if (calcValue(a) == 3 || calcValue(a) == 5 || calcValue(a) == 6)
		{
			int m = max(max(a.poker1.num, a.poker2.num), a.poker3.num);
			int n = max(max(a.poker1.num, a.poker2.num), a.poker3.num);
			if (m > n)
				return 1;
			if (m < n)
				return 0;
			if (m == n)
				return -1;
		}

	}
}
void shuffle(player& player1, player& player2)
{
	int j;
	int t[10];
	t[1] = rand() % 52;
	for (int i = 2; i <= 9; i++)
	{
		while (1)
		{
			int m = rand() % 52;
			for (j = 1; j < i; j++)
				if (t[j] == m)
					break;
			if (j == i)
			{
				t[i] = m;
				break;
			}
		}
	}
	host.poker1.color = t[1] / 13;
	host.poker1.num = t[1] % 13 + 1;
	host.poker2.color = t[4] / 13;
	host.poker2.num = t[4] % 13 + 1;
	host.poker3.color = t[7] / 13;
	host.poker3.num = t[7] % 13 + 1;
	player1.poker1.color = t[2] / 13;
	player1.poker1.num = t[2] % 13 + 1;
	player1.poker2.color = t[5] / 13;
	player1.poker2.num = t[5] % 13 + 1;
	player1.poker3.color = t[8] / 13;
	player1.poker3.num = t[8] % 13 + 1;
	player2.poker1.color = t[3] / 13;
	player2.poker1.num = t[3] % 13 + 1;
	player2.poker2.color = t[6] / 13;
	player2.poker2.num = t[6] % 13 + 1;
	player2.poker3.color = t[9] / 13;
	player2.poker3.num = t[9] % 13 + 1;
	if (host.poker1.num == 1) host.poker3.num = 14;
	if (host.poker2.num == 1) host.poker3.num = 14;
	if (host.poker3.num == 1) host.poker3.num = 14;
	if (player1.poker1.num == 1) player1.poker1.num = 14;
	if (player1.poker2.num == 1) player1.poker2.num = 14;
	if (player1.poker3.num == 1) player1.poker3.num = 14;
	if (player2.poker1.num == 1) player2.poker1.num = 14;
	if (player2.poker2.num == 1) player2.poker2.num = 14;
	if (player2.poker3.num == 1) player2.poker3.num = 14;
	string s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[1] + 1) + ".png";
	loadimage(&host.poker1.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[4] + 1) + ".png";
	loadimage(&host.poker2.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[7] + 1) + ".png";
	loadimage(&host.poker3.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[2] + 1) + " - 副本.png";
	loadimage(&player1.poker1.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[5] + 1) + " - 副本.png";
	loadimage(&player1.poker2.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[8] + 1) + " - 副本.png";
	loadimage(&player1.poker3.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[3] + 1) + " - 副本.png";
	loadimage(&player2.poker1.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[6] + 1) + " - 副本.png";
	loadimage(&player2.poker2.img, s.c_str());
	s = "E:\\大学\\c c++编程实践\\AAA\\resourceImage\\" + to_string(t[9] + 1) + " - 副本.png";
	loadimage(&player2.poker3.img, s.c_str());
}
int actionJudge(player& a, player& b, player& c, int turns, int playerLeft)//1代表下注/跟注 2代表看牌 3代表放弃 4代表开牌
{
	if (playerLeft == 1)
		return 1;
	if (a.character == "循规蹈矩")
	{
		if (turns <= 3)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 7)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 25)
					return 1;
				int t = rand() % 10;
				if (t <= 7)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 17)
					return 1;
				int t = rand() % 10;
				if (t <= 6)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 10)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 5)
							return 4;
						else if (t <= 7)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 6)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 11 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 4)
						return 4;
					else if (t <= 7)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "沉稳")
	{
		if (turns <= 2)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 8)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 20)
					return 1;
				int t = rand() % 10;
				if (t <= 6)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 14)
					return 1;
				int t = rand() % 10;
				if (t <= 5)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 9)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 4)
							return 4;
						else if (t <= 6)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 12)
					return 3;
				if (turns > 6 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 8)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 7)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 10 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 8)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 3)
						return 4;
					else if (t <= 7)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "急躁")
	{
		if (turns <= 3)
			return 1;
		if (turns > 9)
			return 4;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 7)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 25)
					return 1;
				int t = rand() % 10;
				if (t <= 7)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 17)
					return 1;
				int t = rand() % 10;
				if (t <= 6)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 10)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 5)
							return 4;
						else if (t <= 7)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 6)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 11 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 4)
						return 4;
					else if (t <= 7)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "易上头")
	{
		if (turns <= 3)
			return 1;
		if (turns > 12)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 7)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 25)
					return 1;
				int t = rand() % 10;
				if (t <= 7)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 17)
					return 1;
				int t = rand() % 10;
				if (t <= 6)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 10)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 5)
							return 4;
						else if (t <= 7)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 6)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 11 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 4)
						return 4;
					else if (t <= 7)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "冒进")
	{
		if (turns <= 5)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 6)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
				return 1;
			if (calcValue(a) == 4)
			{
				if (turns <= 23)
					return 1;
				int t = rand() % 10;
				if (t <= 7)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 13)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 4)
							return 4;
						else if (t <= 8)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 10)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
				{
					int t = rand() % 10;
					if (t <= 8)
						return 3;
					else
						return 1;
				}
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 8)
							return 3;
						else
							return 1;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 6)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 5)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 14 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 8)
							return 3;
						else
							return 1;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 6)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 4)
						return 4;
					else if (t <= 6)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "胆怯")
	{
		if (turns <= 2)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 8)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 18)
					return 1;
				int t = rand() % 10;
				if (t <= 6)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 13)
					return 1;
				int t = rand() % 10;
				if (t <= 5)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 9)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 3)
							return 4;
						else if (t <= 5)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 6)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 7)
						return 4;
					else
						return 3;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (b.isSeen == 0 && c.isSeen == 0)
					return 1;
				else
					return 3;
			}
			if (calcValue(a) == 2)
			{
				if (turns > 9 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 8)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 2)
						return 4;
					else if (t <= 8)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "冷静")
	{
		if (turns <= 10)
		{
			if (turns <= 3)
				return 1;
			else if (a.isSeen == 0)
			{
				int t = rand() % 10;
				if (t <= 7)
					return 2;
				else
					return 1;
			}
			else
			{
				if (calcValue(a) == 6)
					return 1;
				if (calcValue(a) == 5)
				{
					if (turns <= 25)
						return 1;
					int t = rand() % 10;
					if (t <= 7)
						return 1;
					else
						return 4;
				}
				if (calcValue(a) == 4)
				{
					if (turns <= 17)
						return 1;
					int t = rand() % 10;
					if (t <= 6)
						return 1;
					else
						return 4;
				}
				if (calcValue(a) == 3)
				{
					if (turns <= 10)
						return 1;
					int t = rand() & 10;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
						{
							if (t <= 5)
								return 4;
							else if (t <= 7)
								return 1;
							else
								return 3;
						}
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							if (t <= 7)
								return 4;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
						return 4;
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
				}
				if (calcValue(a) == 1)
				{
					if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
						return 3;
					if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
						return 3;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
							return 3;
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							int t = rand() % 10;
							if (t <= 7)
								return 3;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					{
						int t = rand() % 10;
						if (t <= 6)
							return 3;
						else
							return 4;
					}
				}
				if (calcValue(a) == 2)
				{
					if (turns > 11 && (b.isSeen == 1 || c.isSeen == 1))
						return 3;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
							return 3;
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							int t = rand() % 10;
							if (t <= 7)
								return 3;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					{
						int t = rand() % 10;
						if (t <= 4)
							return 4;
						else if (t <= 7)
							return 3;
						else
							return 1;
					}
				}
			}
		}
		else
		{
			if (turns <= 3)
				return 1;
			else if (a.isSeen == 0)
			{
				int t = rand() % 10;
				if (t <= 7)
					return 2;
				else
					return 1;
			}
			else
			{
				if (calcValue(a) == 6)
					return 1;
				if (calcValue(a) == 5)
				{
					if (turns <= 20)
						return 1;
					int t = rand() % 10;
					if (t <= 6)
						return 1;
					else
						return 4;
				}
				if (calcValue(a) == 4)
				{
					if (turns <= 15)
						return 1;
					int t = rand() % 10;
					if (t <= 5)
						return 1;
					else
						return 4;
				}
				if (calcValue(a) == 3)
				{
					if (turns <= 8)
						return 1;
					int t = rand() & 10;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
						{
							if (t <= 4)
								return 4;
							else if (t <= 7)
								return 1;
							else
								return 3;
						}
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							if (t <= 7)
								return 4;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
						return 4;
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
				}
				if (calcValue(a) == 1)
				{
					if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 12)
						return 3;
					if (turns > 6 && (b.isSeen == 1 || c.isSeen == 1))
						return 3;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
							return 3;
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							int t = rand() % 10;
							if (t <= 8)
								return 3;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 4;
					}
				}
				if (calcValue(a) == 2)
				{
					if (turns > 9 && (b.isSeen == 1 || c.isSeen == 1))
						return 3;
					if (playerLeft == 3)
					{
						if (b.isSeen == 1 && c.isSeen == 1)
							return 3;
						else if (b.isSeen == 1 || c.isSeen == 1)
						{
							int t = rand() % 10;
							if (t <= 8)
								return 3;
							else
								return 1;
						}
						else
							return 1;
					}
					if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
						return 1;
					if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					{
						int t = rand() % 10;
						if (t <= 3)
							return 4;
						else if (t <= 7)
							return 3;
						else
							return 1;
					}
				}
			}
		}
	}
	if (a.character == "吝啬")
	{
		if (turns <= 2)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 8)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 25)
					return 1;
				int t = rand() % 10;
				if (t <= 8)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 17)
					return 1;
				int t = rand() % 10;
				if (t <= 7)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 10)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 4)
							return 4;
						else if (t <= 6)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 6)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 7)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 11 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 7)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 3)
						return 4;
					else if (t <= 7)
						return 3;
					else
						return 1;
				}
			}
		}
	}
	if (a.character == "慷慨")
	{
		if (turns <= 5)
			return 1;
		else if (a.isSeen == 0)
		{
			int t = rand() % 10;
			if (t <= 6)
				return 2;
			else
				return 1;
		}
		else
		{
			if (calcValue(a) == 6)
				return 1;
			if (calcValue(a) == 5)
			{
				if (turns <= 25)
					return 1;
				int t = rand() % 10;
				if (t <= 8)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 4)
			{
				if (turns <= 17)
					return 1;
				int t = rand() % 10;
				if (t <= 5)
					return 1;
				else
					return 4;
			}
			if (calcValue(a) == 3)
			{
				if (turns <= 10)
					return 1;
				int t = rand() & 10;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
					{
						if (t <= 5)
							return 4;
						else if (t <= 7)
							return 1;
						else
							return 3;
					}
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						if (t <= 7)
							return 4;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
					return 4;
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
			}
			if (calcValue(a) == 1)
			{
				if (max(max(a.poker1.num, a.poker2.num), a.poker3.num) <= 11)
					return 3;
				if (turns > 7 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 6)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 5)
						return 3;
					else
						return 4;
				}
			}
			if (calcValue(a) == 2)
			{
				if (turns > 13 && (b.isSeen == 1 || c.isSeen == 1))
					return 3;
				if (playerLeft == 3)
				{
					if (b.isSeen == 1 && c.isSeen == 1)
						return 3;
					else if (b.isSeen == 1 || c.isSeen == 1)
					{
						int t = rand() % 10;
						if (t <= 6)
							return 3;
						else
							return 1;
					}
					else
						return 1;
				}
				if (playerLeft == 2 && ((b.isSeen == 0 && b.isGivenUp == 0) || (c.isSeen == 0 && c.isGivenUp == 0)))
					return 1;
				if (playerLeft == 2 && ((b.isSeen == 1 && b.isGivenUp == 0) || (c.isSeen == 1 && c.isGivenUp == 0)))
				{
					int t = rand() % 10;
					if (t <= 5)
						return 4;
					else if (t <= 6)
						return 3;
					else
						return 1;
				}
			}
		}
	}
}
void displayCards(player a, int num)
{
	if (num == 1)
	{
		putimage(290, 420, &a.poker1.img);
		putimage(330, 420, &a.poker2.img);
		putimage(370, 420, &a.poker3.img);
	}
	if (num == 2)
	{
		putimage(100, 240, &a.poker1.img);
		putimage(100, 280, &a.poker2.img);
		putimage(100, 320, &a.poker3.img);
	}
	if (num == 3)
	{
		putimage(525, 240, &a.poker1.img);
		putimage(525, 280, &a.poker2.img);
		putimage(525, 320, &a.poker3.img);
	}
}
void initPlayer(player& a)
{
	a.age = rand() % 60 + 18; //未成年人禁止赌博
	DataBaseRoll(a.name, a.sex, a.character);
	int p = host.money * 130 / 100;
	int q = host.money * 70 / 100;
	a.money = rand() % (p - q) + q;
	fameJudge(a);
}
void fameJudge(player& a)
{
	if (a.money <= 1000) a.fame = "一贫如洗";
	if (a.money > 1000 && a.money < 2000) a.fame = "第一桶金";
	if (a.money >= 2000 && a.money < 10000) a.fame = "小有起色";
	if (a.money >= 10000 && a.money < 100000) a.fame = "赌场老成";
	if (a.money >= 100000 && a.money < 1000000) a.fame = "赌场高手";
	if (a.money >= 1000000 && a.money < 50000000) a.fame = "赌场教父";
	if (a.money >= 50000000) a.fame = "赌王之王";
}
void DataBaseRoll(string& name, string& sex, string& character)
{//随机生成函数
	 //百家姓-单姓
	rand();
	string NA1[444] = { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常", "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟", "平", "黄", "和", "穆", "萧", "尹", "姚", "邵", "湛", "汪", "祁", "毛", "禹", "狄", "米", "贝", "明", "臧", "计", "伏", "成", "戴", "谈", "宋", "茅", "庞", "熊", "纪", "舒", "屈", "项", "祝", "董", "梁", "杜", "阮", "蓝", "闵", "席", "季", "麻", "强", "贾", "路", "娄", "危", "江", "童", "颜", "郭", "梅", "盛", "林", "刁", "钟", "徐", "邱", "骆", "高", "夏", "蔡", "田", "樊", "胡", "凌", "霍", "虞", "万", "支", "柯", "昝", "管", "卢", "莫", "经", "房", "裘", "缪", "干", "解", "应", "宗", "丁", "宣", "贲", "邓", "郁", "单", "杭", "洪", "包", "诸", "左", "石", "崔", "吉", "钮", "龚", "程", "嵇", "邢", "滑", "裴", "陆", "荣", "翁", "荀", "羊", "於", "惠", "甄", "麴", "家", "封", "芮", "羿", "储", "靳", "汲", "邴", "糜", "松", "井", "段", "富", "巫", "乌", "焦", "巴", "弓", "牧", "隗", "山", "谷", "车", "侯", "宓", "蓬", "全", "郗", "班", "仰", "秋", "仲", "伊", "宫", "宁", "仇", "栾", "暴", "甘", "钭", "厉", "戎", "祖", "武", "符", "刘", "景", "詹", "束", "龙", "叶", "幸", "司", "韶", "郜", "黎", "蓟", "薄", "印", "宿", "白", "怀", "蒲", "邰", "从", "鄂", "索", "咸", "籍", "赖", "卓", "蔺", "屠", "蒙","池", "乔", "阴", "郁", "胥", "能", "苍", "双", "闻", "莘", "党", "翟", "谭", "贡", "劳", "逄", "姬", "申", "扶", "堵", "冉", "宰", "郦", "雍", "舄", "璩", "桑", "桂", "濮", "牛", "寿", "通", "边", "扈", "燕", "冀", "郏", "浦", "尚", "农", "温", "别", "庄", "晏", "柴", "瞿", "阎", "充", "慕", "连", "茹", "习", "宦", "艾", "鱼", "容", "向", "古", "易", "慎", "戈", "廖", "庾", "终", "暨", "居", "衡", "步", "都", "耿", "满", "弘", "匡", "国", "文", "寇", "广", "禄", "阙", "东", "殴", "殳", "沃", "利", "蔚", "越", "夔", "隆", "师", "巩", "厍", "聂", "晁", "勾", "敖", "融", "冷", "訾", "辛", "阚", "那", "简", "饶", "空", "曾", "毋", "沙", "乜", "养", "鞠", "须", "丰", "巢", "关", "蒯", "相", "查", "後", "荆", "红", "游", "竺", "权", "逯", "盖", "益", "桓", "公", "仉", "督", "晋", "楚", "闫", "法", "汝", "鄢", "涂", "钦", "归", "海","岳", "帅", "缑", "亢", "况", "后", "有", "琴", "商", "牟", "佘", "佴", "伯", "赏", "墨", "哈", "谯", "笪", "年", "爱", "阳", "佟", "言", "福" };
	//百家姓-复姓
	string NA2[59] = { "万俟", "司马", "上官", "欧阳", "夏侯", "诸葛", "闻人", "东方", "赫连", "皇甫", "尉迟", "公羊", "澹台", "公冶", "宗政", "濮阳", "淳于", "单于", "太叔", "申屠", "公孙", "仲孙", "轩辕", "令狐", "钟离", "宇文", "长孙", "慕容", "鲜于", "闾丘", "司徒", "司空", "亓官", "司寇", "子车", "颛孙", "端木", "巫马", "公西", "漆雕", "乐正", "壤驷", "公良", "拓跋", "夹谷", "宰父", "谷梁", "百里", "东郭", "南门", "呼延", "羊舌", "微生", "梁丘", "左丘", "东门", "西门", "南宫", "第五" };
	//男性常用名
	string ME1m[140] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴", "良", "海", "山", "仁", "波", "宁", "贵", "福", "生", "龙", "元", "全", "国", "胜", "学", "祥", "才", "发", "武", "新", "利", "清", "飞", "彬", "富", "顺", "信", "子", "杰", "涛", "昌", "成", "康", "星", "光", "天", "达", "安", "岩", "中", "茂", "进", "林", "有", "坚", "和", "彪", "博", "诚", "先", "敬", "震", "振", "壮", "会", "思", "群", "豪", "心", "邦", "承", "乐", "绍", "功", "松", "善", "厚", "庆", "磊", "民", "友", "裕", "河", "哲", "江", "超", "浩", "亮", "政", "谦", "亨", "奇", "固", "之", "轮", "翰", "朗", "伯", "宏", "言", "若", "鸣", "朋", "斌", "梁", "栋", "维", "启", "克", "伦", "翔", "旭", "鹏", "泽", "晨", "辰", "士", "以", "建", "家", "致", "树", "炎", "德", "行", "时", "泰", "盛" };
	//女性常用名
	string ME1f[165] = { "秀", "娟", "英", "华", "慧", "巧", "美", "娜", "静", "淑", "惠", "珠", "翠", "雅", "芝", "玉", "萍", "红", "娥", "玲", "芬", "芳", "燕", "彩", "春", "菊", "兰", "凤", "洁", "梅", "琳", "素", "云", "莲", "真", "环", "雪", "荣", "爱", "妹", "霞", "香", "月", "莺", "媛", "艳", "瑞", "凡", "佳", "嘉", "琼", "勤", "珍", "贞", "莉", "桂", "娣", "叶", "璧", "璐", "娅", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "姣", "婉", "娴", "瑾", "颖", "露", "瑶", "怡", "婵", "雁", "蓓", "纨", "仪", "荷", "丹", "蓉", "眉", "君", "琴", "蕊", "薇", "菁", "梦", "岚", "苑", "筠", "柔", "竹", "霭", "凝", "晓", "欢", "霄", "枫", "芸", "菲", "寒", "欣", "滢", "伊", "亚", "宜", "可", "姬", "舒", "影", "荔", "枝", "思", "丽", "秀", "飘", "育", "馥", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "宁","蓓", "纨", "苑", "婕", "馨", "瑗", "琰", "韵", "融", "园", "艺", "咏", "卿", "聪", "澜", "纯", "毓", "悦", "昭", "冰", "爽", "琬", "茗", "羽", "希" };
	string CHAR[9] = { "沉稳","急躁","吝啬","慷慨","冒进","胆怯","冷静","易上头","循规蹈矩" };
	sex = (rand() % 2 == 0 ? "男" : "女");//男女选择
	character = CHAR[rand() % 9];
	name = (rand() % 56 != 5 ? NA1[rand() % 444] : NA2[rand() % 59]);//单姓Or复姓选择
	name += (sex == "男" ? ME1m[rand() % 140] : ME1f[rand() % 165]);//取名第一字
	if (rand() % 2 == 0) name += (sex == "男" ? ME1m[rand() % 140] : ME1f[rand() % 165]);//取名第二字
}
