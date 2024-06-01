#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
//goto function to move the cursor to a specific position
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//This function is used to change the colour of the cursor
void colorit(int col)
{
    HANDLE hstdout;
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, col);
}
//this function is used in the whole program to clear the entire screen within the borders
void cleartxt()
{
	int i,j;
	gotoxy(0,0);
	printf("                                                          ");
	for(i=1; i<130; ++i)
	{
		for(j=2; j<31; ++j)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
}
//for intro border
void border();
//for menu
void menu();
//The first mode which provides the typing speed of the user
void typingspeed()
{
	int i,j,k,key,index=1;
	char answer[20];
    int compare, value, count=0, z=10;
    float sum=0;
    char words[100][20] = {
        "Suddenly", "Announcing", "Introducing", "Improvement", "Amazing",
        "Sensational", "Remarkable", "Revolutionary", "Startling", "Exclusive",
        "Unbelievable", "Incredible", "Revealed", "Sensational", "Guaranteed",
        "Revolutionary", "Astonishing", "Unmissable", "Undoubtedly", "Compelling",
        "Enlightening", "Emphatically", "Essentially", "Decisively", "Colonel",
        "Adventure", "Beautiful", "Captivating", "Delightful", "Eccentric",
        "Fantastic", "Gorgeous", "Harmonious", "Intriguing", "Jubilant",
        "Kaleidoscopic", "Luminous", "Majestic", "Nostalgic", "Opulent",
        "Picturesque", "Quaint", "Radiant", "Spectacular", "Tranquil",
        "Uplifting", "Vibrant", "Whimsical", "Exquisite", "Serendipity",
        "Breathtaking", "Symphony", "Effervescent", "Resplendent", "Enchanting",
        "Mellifluous", "Cacophony", "Petrichor", "Limerence", "Sonorous",
        "Panorama", "Ephemeral", "Halcyon", "Aurora", "Epiphany",
        "Quixotic", "Nebula", "Vorfreude", "Labyrinthine", "Solitude",
        "Efflorescence", "Cynosure", "Evanescent", "Sonnet", "Bucolic",
        "Ebullient", "Luminescence", "Ineffable", "Mellifluous", "Halcyon",
        "Supine", "Serendipity", "Idyllic", "Benevolent", "Crepuscule",
        "Aplomb", "Vorfreude", "Serene", "Incandescent", "Amorphous",
        "Ephemeral", "Ineffable", "Evocative", "Limerence", "Cacophony",
        "Aurora", "Resplendent", "Mellifluous", "Panorama", "Quixotic"
    };
	cleartxt();
    srand(time(NULL));
    time_t begin, finish;
    double elapsed;
    for (k=0; k<10; ++k) 
	{
        value = rand() % 100;
        gotoxy(2, 2);
        printf("WORD = %s\n", words[value]);
        while(1)
        {
        	gotoxy(2, 3);
        	if(kbhit())
        	{
        		time(&begin);
        		gets(answer);
        		break;
			}
		}
        time(&finish);
        elapsed = difftime(finish, begin);//to calculate the time interval
        sum = sum + elapsed;
        compare = strcmp(words[value], answer);
        if (compare == 0) 
		{
			gotoxy(2, 4);
            printf("entered word is correct");
            count = count + 1;
        }
        else 
		{
			gotoxy(2, 4);
            printf("incorrect word");
            z = z -1;//to calculate the score
    	}
    	gotoxy(2, 6);
    	printf("Press Enter");
    	while(1)
        {
        	key=getch();
        	if(key==13)
        	{
        		break;
			}
		}
		cleartxt();
    }
    gotoxy(59, 13);
    printf("Your total score is %d", count);
    gotoxy(59, 14);
    printf("Your typing accuracy is %d%% ", (z*100)/10);
    gotoxy(59, 15);
    printf("Your average typing speed is %.2f words/sec", sum/10);
    key='\0';
	while(key!=13)
	{
		gotoxy(59, 17);
		colorit(143);
		if(index==1)
		{
			colorit(129);
		}
		printf("Try Again");
		gotoxy(59, 18);
		colorit(143);
		if(index==2)
		{
			colorit(129);
		}
		printf("Main menu");
		key=getch();
		if(key==80)
		{
			++index;
		}
		if(key==72)
		{
			--index;
		}
		if(index==3)
		{
			index=1;
		}
		if(index==0)
		{
			index=2;
		}
	}
	if(index==1)
	{
		typingspeed();
	}
	if(index==2)
	{
		colorit(143);
		menu();
	}
}
//to count the number of users who have played the typing tasks mode
int countLines1(void){
	FILE *fptr;
	fptr = fopen("typingtasks.txt", "r");
    if (fptr == NULL) {
        return 0;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    fclose(fptr);
	return count;
}
//to add a new user to the file for typing tasks leaderboard
void editLeaderboard1(char *name , int level){
	FILE *fptr;
	fptr = fopen("typingtasks.txt", "a");
	fprintf(fptr, "%s %d\n", name, level);
	fclose(fptr);
}
//to display the leaderboard for typing tasks mode
void displayLeaderboard1(void){
    int entries = countLines1();
	FILE *fptr;
    char names[1000][15], tnames[1000][15];
    int levels[1000], tlevels[1000], i, j;
	cleartxt();
    gotoxy(59,10);
    printf("TYPING TASKS");
    fptr = fopen("typingtasks.txt", "r");
    int key;
    if(entries == 0){
    	gotoxy(45, 13);
    	printf("Leaderboard has not been created yet.");
    	gotoxy(59, 17);
    	colorit(129);
    	printf("Back");
    	key='\0';
    	while(key!=13)
    	{
    		key=getch();
    	}
    	colorit(143);
    	menu();
	}
	for(i=0;i<entries;i++){
		fscanf(fptr, "%s %d", names[i], &levels[i]);
	}	
	fclose(fptr);
	for(i=0;i<(entries-1);i++){
		for(j=i+1;j<entries;j++){
			if (levels[i] < levels[j]){
				int temp = levels[i];
				levels[i] = levels[j];
				levels [j] = temp;
				char tempstring[15];
				strcpy(tempstring, names[i]);
				strcpy(names[i], names[j]);
				strcpy(names[j], tempstring);
			}
		}
	}
	gotoxy(50, 11);
	printf("Name");
	gotoxy(77,11);
	printf("Level");
	for(i=0;i<5;i++){
		if(levels[i]!=0)
		{
			gotoxy(50, 13+i);
			printf("%s", names[i]);
			gotoxy(79, 13+i);
			printf("%d", levels[i]);
		}
	}
	gotoxy(65, 20);
	colorit(129);
	printf("Back");
    key='\0';
    while(key!=13)
    {
    	key=getch();
    }
    colorit(143);
    menu();
}
// Function to compare and adjust spaces
int compareAndAdjustSpaces(char *original, char *input) {
    int mistakes = 0;
    int len = strlen(original);
    int i, j;
    for (i = 0; i < len; i++) {
        if (original[i] == ' ' && input[i] != ' ') {
            // Inserting space in input at the same position
            for (j = len; j > i; j--) {
                input[j] = input[j - 1];
            }
            input[i] = ' ';
            mistakes++;
        } else if (original[i] != ' ' && input[i] == ' ') {
            // Removing space from input at the same position
            for (j = i; j < len; j++) {
                input[j] = input[j + 1];
            }
            mistakes++;
        }
    }
    return mistakes;
}
// Function to check spelling errors in individual words
int checkSpellingErrors(char *original, char *input) {
    int mistakes = 0;
    char originalTokens[50][50];
    char inputTokens[50][50];
    int originalTokenCount = 0;
    int inputTokenCount = 0;
    int i;
    // Tokenizing the original paragraph
    char *originalToken = strtok(original, " ");
    while (originalToken != NULL) {
        strcpy(originalTokens[originalTokenCount], originalToken);
        originalToken = strtok(NULL, " ");
        originalTokenCount++;
    }
    // Tokenizing the input paragraph
    char *inputToken = strtok(input, " ");
    while (inputToken != NULL) {
        strcpy(inputTokens[inputTokenCount], inputToken);
        inputToken = strtok(NULL, " ");
        inputTokenCount++;
    }
    // Compare words in the arrays for spelling errors
    for (i = 0; i < originalTokenCount; i++) {
        if (strcmp(originalTokens[i], inputTokens[i]) != 0) {
            mistakes++;
        }
    }
    return mistakes;
}
//the functioning of the 2nd mode typing tasks
void typingtasks() {
	char userName[15];
	int index=1;
	char paragraph[10][500] = {"I love to play in the park. The sun shines brightly as kids run and laugh. We play on the swings, slides, and monkey bars. It's great fun to be outside and enjoy the fresh air with my friends.",
							   "After we're done at the park, we head back home. Mom makes us delicious sandwiches for lunch. I like mine with ham and cheese. It tastes fantastic! I also enjoy having a glass of cold milk with my sandwich.",
							   "In the evening, I have piano lessons at the music school. I practice the scales and learn new songs. My teacher is patient and helps me improve my technique. I like playing the piano because it sounds beautiful.",
							   "Every summer, my family goes on vacation to an exotic location. Last year, we explored the breathtaking beaches of the Caribbean. The crystal-clear water and soft white sand were enchanting. We swam, sunbathed, and built sandcastles.",
							   "At school, we have captivating science experiments in the lab. One time, we mixed different substances and observed colorful chemical reactions. We also learned about the solar system and how the planets orbit the sun. Science class is fascinating.",
							   "History class is intriguing as well. We study ancient civilizations, like the Egyptians and Greeks. I find it fascinating how they built majestic pyramids and created intricate sculptures. Learning about the past helps us understand our world today.",
							   "English class can be challenging sometimes, especially when we have to write essays. We study Shakespeare's plays and analyze complex characters and themes. I always try my best to express my thoughts clearly on paper.",
							   "Math class can be tough, but I enjoy solving problems. Algebra requires logical thinking and finding x, y, and z values. Geometry is interesting too, with its different shapes and formulas. Math helps us understand patterns and make sense of the world.",
							   "In high school, I took a challenging chemistry course. We delved deeper into the periodic table and learned about atoms, molecules, and chemical bonds. Experiments became more advanced, like titrations and determining reaction rates.",
							   "Now in college, I'm studying neuroscience, which involves intricate knowledge of the brain and nervous system. I've learned about neurotransmitters, neural pathways, and how different areas of the brain control specific functions. It's a complex field, but incredibly fascinating."};
    char tempparagraph[500];
	int x = 0;
    int i, j;
    while (x!=1){
    	x=0;
		cleartxt();
		for(i=0; i<15; ++i)
		{
			userName[i]='\0';
		}
		gotoxy(2,2);
		printf("Enter your name (not more than 15 characters and no spaces) : ");
        gets(userName);
        for(i=0;i<15;i++){
        	if(userName[i]==32){
        		x=2;
			}
		}
		if(x==2){
			gotoxy(2,3);
			printf("Name should not contain spaces.");
			sleep(2);
			continue;
		}
		if(strlen(userName) <= 15){
    	    x=1;
	    }
	    else{
	    	gotoxy(2,3);
			printf("Name should not be longer than 15 characters.\n\n");
	    	sleep(2);
		}
    }
    int o=0;
    while (o<10) {
		system("cls");
		char userInput[500];
        char adjustedInput[500];
        char key;
        int spaceMistakes=0, spellingMistakes=0, totalMistakes=0;
        int initialTime=0, finalTime=0, elapsedTime=0, limitTime= 85 - (o*5);
        int endGame=0;
		gotoxy(0,0);
		printf("                                                                      ");
		gotoxy(0,0);
        printf("Level %d\t\tTime limit:%d sec", o+1, limitTime);
	    printf("\n\nType the following paragraph and hit ENTER:\n\n%s\n\n", paragraph[o]);
        printf("Press ENTER to begin the level. ");
        do {
		    key = getch();
		} while (key != 13);
        // Countdown to begin the level
		printf("\nThe level begins in 3... ");
        sleep(1);
        printf("2... ");
        sleep(1);
        printf("1... ");
        sleep(1);
        printf("GO!\n\n");
        initialTime = time(NULL);
	    scanf("%[^\n]s", userInput);
	    fflush(stdin);
	    finalTime = time(NULL);
	    elapsedTime = finalTime - initialTime;
	    // Check whether user surpassed the time limit
		if(elapsedTime > limitTime){
		    printf("You took too much time!");
		    key='\0';
		    while(key!=13)
			{
				gotoxy(59, 17);
				colorit(143);
				if(index==1)
				{
					colorit(129);
				}
				printf("Retry");
				gotoxy(59, 18);
				colorit(143);
				if(index==2)
				{
					colorit(129);
				}
				printf("Main menu");
				key=getch();
				if(key==80)
				{
					++index;
				}
				if(key==72)
				{
					--index;
				}
				if(index==3)
				{
					index=1;
				}
				if(index==0)
				{
					index=2;
				}
			}
			if(index==1)
			{
				continue;
			}
			if(index==2)
			{
				system("cls");
				editLeaderboard1(userName, o);
				colorit(143);
				border();
				menu();
			}
	    }
	    else{
		    strcpy(adjustedInput, userInput);
		    strcpy(tempparagraph, paragraph[o]);
            // Compare and adjust spaces
            spaceMistakes = compareAndAdjustSpaces(tempparagraph, adjustedInput);
            // Check spelling errors in individual words
            spellingMistakes = checkSpellingErrors(tempparagraph, adjustedInput);
            totalMistakes = spaceMistakes + spellingMistakes;
            if (totalMistakes > 3) {
                printf("\nYou have made too many mistakes.");
            	key='\0';
  	    	    while(key!=13)
				{
					gotoxy(59, 17);
					colorit(143);
					if(index==1)
					{
						colorit(129);
					}
					printf("Retry");
					gotoxy(59, 18);
					colorit(143);
					if(index==2)
					{
						colorit(129);
						}
					printf("Main menu");
					key=getch();
					if(key==80)
					{
						++index;
					}
					if(key==72)
					{
						--index;
					}
					if(index==3)
					{
						index=1;
					}
					if(index==0)
					{
						index=2;
					}
				}
				if(index==1)
				{
					continue;
				}
				if(index==2)
				{
					system("cls");
					editLeaderboard1(userName, o);
					colorit(143);
					border();
					menu();
				}
           	}
			else {
				if(o==9)
				{
					++o;
					endGame=1;
				}
				else
				{
	                printf("\nCongratulations! You have entered the paragraph correctly.");
    	            key='\0';
   	    	        while(key!=13)
					{
						gotoxy(59, 17);
						colorit(143);
						if(index==1)
						{
							colorit(129);
						}
						printf("Next level");
						gotoxy(59, 18);
						colorit(143);
						if(index==2)
						{
							colorit(129);
						}	
						printf("End game");
						key=getch();
						if(key==80)
						{
							++index;
						}
						if(key==72)
						{
							--index;
						}
						if(index==3)
						{
							index=1;
						}
						if(index==0)
						{
							index=2;
						}
					}
					if(index==1)
					{
						++o;
						continue;
					}
					if(index==2)	
					{
						endGame=1;
						++o;
						colorit(143);
					}
   		        }
   		    }
	   	}
	    if (endGame == 1){
		
		    editLeaderboard1(userName, o);
		    system("cls");
		    for(i=0; i<=130; i++)
			{
				gotoxy(i, 1);	
				printf("*");
				gotoxy(i, 31);
				printf("*");
			}
			for(i=0; i<30; i++)
			{
				gotoxy(0, i+1);	
				printf("*");
				gotoxy(130, i+1);
				printf("*");
			}
			gotoxy(59, 14);
		    printf("Name : %s", userName);
		    gotoxy(59, 15);
		    printf("Levels completed : %d", o);
			key='\0';
  	    	while(key!=13)
			{
				gotoxy(59, 17);
				colorit(143);
				if(index==1)
				{
					colorit(129);
				}
				printf("Leaderboard");
				gotoxy(59, 18);
				colorit(143);
				if(index==2)
				{
					colorit(129);
				}
				printf("Main menu");
				key=getch();
				if(key==80)
				{
					++index;
				}
				if(key==72)
				{
					--index;
				}
				if(index==3)
				{
					index=1;
				}
				if(index==0)
				{
					index=2;
				}
			}
			if(index==1)
			{
				colorit(143);
				displayLeaderboard1();
			}
			if(index==2)
			{
				system("cls");
				colorit(143);
				border();
				menu();
			}
        }
    }
}
//to add a new user to the file for leaderboard of typing game
void editLeaderboard2(char *name , int level){
	FILE *fptr;
	fptr = fopen("typinggame.txt", "a");
	fprintf(fptr, "%s %d\n", name, level);
	fclose(fptr);
}
//this counts the number of user who had played the typing game mode
int countLines2(void){
	FILE *fptr;
	fptr = fopen("typinggame.txt", "r");
    if (fptr == NULL) {
        return 0;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    fclose(fptr);
	return count;
}
//to display the leaderboard for typing game mode
void displayLeaderboard2(void){
    int entries = countLines2();
	FILE *fptr;
    char names[1000][15];
    int scores[1000], i, j;
	cleartxt();
    gotoxy(59,10);
    printf("TYPING GAME");
    fptr = fopen("typinggame.txt", "r");
    int key;
    if(entries == 0){
    	gotoxy(45, 13);
    	printf("Leaderboard has not been created yet.");
    	gotoxy(59, 17);
    	colorit(129);
    	printf("Back");
    	key='\0';
    	while(key!=13)
    	{
    		key=getch();
    	}
    	colorit(143);
    	menu();
	}
	for(i=0;i<entries;i++){
		fscanf(fptr, "%s %d", names[i], &scores[i]);
	}	
	fclose(fptr);
	for(i=0;i<(entries-1);i++){
		for(j=i+1;j<entries;j++){
			if (scores[i] < scores[j]){
				int temp = scores[i];
				scores[i] = scores[j];
				scores [j] = temp;
				char tempstring[15];
				strcpy(tempstring, names[i]);
				strcpy(names[i], names[j]);
				strcpy(names[j], tempstring);
			}
		}
	}
	gotoxy(50, 11);
	printf("Name");
	gotoxy(77,11);
	printf("Score");
	for(i=0;i<5;i++){
		if(scores[i]!=0)
		{
			gotoxy(50, 13+i);
			printf("%s", names[i]);
			gotoxy(79, 13+i);
			printf("%d", scores[i]);
		}
	}
	gotoxy(65, 20);
	colorit(129);
	printf("Back");
    key='\0';
    while(key!=13)
    {
    	key=getch();
    }
    colorit(143);
    menu();
}
//functioning of typing game mode
void typinggame()
{
	int i, j, k;
	char userName[15];
	cleartxt();
	while (k!=1){
		cleartxt();
		k=0;
		gotoxy(2,2);
		for(i=0; i<15; ++i)
		{
			userName[i]='\0';
		}
		printf("Enter your name (not more than 15 characters and no spaces) : ");
        gets(userName);
        for(i=0;i<15;i++){
        	if(userName[i]==32){
        		k=2;
			}
		}
		if(k==2){
			gotoxy(2,3);
			printf("Name should not contain spaces.");
			sleep(2);
			continue;
		}
		if(strlen(userName) <= 15){
    	    k=1;
	    }
	    else{
	    	gotoxy(2,3);
			printf("Name should not be longer than 15 characters.");
	    	sleep(2);
	    	continue;
		}
    }
    srand(time(NULL));
	int key,index=1;
    int score = 0;
    int level = 1;
    char letter1 = 'A' + rand() % 26;//generating a random letter
    int x = rand() % 130;//generating a random position
    if(x==0||x==130)
    {
        x=1;
	}
    int y = 2;
	cleartxt();
	gotoxy(0, 0);
	printf("                                                 ");
	gotoxy(0, 0);
    printf("Score: %d\t\t\tLevel: %d", score, level);
    while (1) {
        gotoxy(x, y);
        colorit(143);
        printf("%c", letter1);
        Sleep(1000/(level*5));//controls the speed of falling letter w.r.t to levels
    	printf("\b ");
        // Check for user input
        if (kbhit()) {
            char input = getch();
            if (input == letter1||input==letter1+32) {
                ++score;
                if (score > 0 && score % 10 == 0) {
                    level += 1;
                }
                gotoxy(0,0);
                colorit(143);
                printf("Score: %d\t\t\tLevel: %d", score, level);
                letter1 = 'A' + rand() % 26;
                x = rand() % 130;
                if(x==0||x==130)
                {
                	x=1;
				}
                y = 2;
            }
        }
		++y;
        if(y==31)//if the letter touches the bottom line
        {
        	colorit(143);
        	gotoxy(59, 13);
        	printf("GAME OVER!");
        	gotoxy(59, 14);
        	printf("Score:%d", score);
			while(key!=13)
			{
				gotoxy(59, 15);
				colorit(143);
				if(index==1)
				{
					colorit(129);
				}
				printf("Try Again");
				gotoxy(59, 16);
				colorit(143);
				if(index==2)
				{
					colorit(129);
				}
				printf("Main menu");
				key=getch();
				if(key==80)
				{
					++index;
				}
				if(key==72)
				{
					--index;
				}
				if(index==3)
				{
					index=1;
				}
				if(index==0)
				{
					index=2;
				}
			}
			if(index==1)
			{
				editLeaderboard2(userName, score);
				typinggame();
			}
			if(index==2)
			{
				editLeaderboard2(userName, score);
				colorit(143);
				gotoxy(0,0);
				printf("                                                          ");
				menu();
			}
		}
    }
}
//the intro border
void border()
{
	int i;
	for(i=0; i<=65; i++)
	{
		gotoxy(65-i, 1);
		printf("*");
		gotoxy(65+i, 1);
		printf("*");
		usleep(1000);
	}
	for(i=0; i<30; i++)
	{
		gotoxy(0, i+1);
		printf("*");
		gotoxy(130, i+1);
		printf("*");
		usleep(1000);
	}
	for(i=0; i<=65; i++)
	{
		gotoxy(130-i, 31);
		printf("*");
		gotoxy(i, 31);
		printf("*");
		usleep(1000);
	}
}

void menu()
{
	int i,j;
	const char *msg=" TYPING TUTOR";
	const char *msg0="Select Modes";
	const char *msg1="Leaderboard";
	const char *msg2="Help";
	const char *msg3="Exit";
	const char *msg4="Typing Speed Test";
	const char *msg5="Typing Tasks";
	const char *msg6="Typing Game";
	const char *msg7="Back";
	const char *msg8="MODES";
	const char *msg9="LEADERBOARD";
	const char *msg10="HELP";
	cleartxt();
	colorit(143);
	for(i=0; i<13; ++i)
	{
		usleep(1000);
		gotoxy(59+i, 10);
		printf("%c", msg[i]);
	}
	for(i=0; i<12; ++i)
	{
		usleep(1000);
		gotoxy(59+i, 13);
		printf("%c", msg0[i]);
	}
	for(i=0; i<11; ++i)
	{
		usleep(1000);
		gotoxy(59+i, 14);
		printf("%c", msg1[i]);
	}
	for(i=0; i<4; ++i)
	{
		usleep(1000);
		gotoxy(59+i, 15);
		printf("%c", msg2[i]);
	}
	for(i=0; i<4; ++i)
	{
		usleep(1000);
		gotoxy(59+i, 16);
		printf("%c", msg3[i]);
	}
	int index=1;
	char key;
	while(key!=13)
	{
		gotoxy(59, 10);
		colorit(143);
		printf(" TYPING TUTOR");
		gotoxy(59, 13);
		colorit(143);
		if(index==1)
		{
			colorit(129);
		}
		printf("Select Modes");
		gotoxy(59, 14);
		colorit(143);
		if(index==2)
		{
			colorit(129);
		}
		printf("Leaderboard");
		gotoxy(59, 15);
		colorit(143);
		if(index==3)
		{
			colorit(129);
		}
		printf("Help");
		gotoxy(59, 16);
		colorit(143);
		if(index==4)
		{
			colorit(129);
		}
		printf("Exit");
		colorit(143);
		key=getch();
		if(key==80)
		{
			++index;
		}
		if(key==72)
		{
			--index;
		}
		if(index==5)
		{
			index=1;
		}
		if(index==0)
		{
			index=4;
		}
	}
	if(index==1)
	{
		int index=1;
		char key;
		cleartxt();
		for(i=0; i<5; ++i)
		{
			usleep(1000);
			gotoxy(61+i, 10);
			printf("%c", msg8[i]);
		}
		for(i=0; i<17; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 13);
			printf("%c", msg4[i]);
		}
		for(i=0; i<12; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 14);
			printf("%c", msg5[i]);
		}
		for(i=0; i<11; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 15);
			printf("%c", msg6[i]);
		}
		for(i=0; i<4; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 16);
			printf("%c", msg7[i]);
		}
		while(key!=13)
		{
			gotoxy(59, 13);
			colorit(143);
			if(index==1)
			{
				colorit(138);
			}
			printf("Typing Speed Test");
			gotoxy(59, 14);
			colorit(143);
			if(index==2)
			{
				colorit(138);
			}
			printf("Typing Tasks");
			gotoxy(59, 15);
			colorit(143);
			if(index==3)
			{
				colorit(138);
			}
			printf("Typing Game");
			gotoxy(59, 16);
			colorit(143);
			if(index==4)
			{
				colorit(138);
			}
			printf("Back");
			colorit(143);
			key=getch();
			if(key==80)
			{
				++index;
			}
			if(key==72)
			{
				--index;
			}
			if(index==5)
			{
				index=1;
			}
			if(index==0)
			{
				index=4;
			}
		}
		if(index==1)
		{
			typingspeed();
		}
		if(index==2)
		{
			typingtasks();
		}
		if(index==3)
		{
			typinggame();
		}
		if(index==4)
		{
			menu();
		}
	}
	if(index==2)
	{
		cleartxt();
		for(i=0; i<11; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 10);
			printf("%c", msg9[i]);
		}
		for(i=0; i<12; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 13);
			printf("%c", msg5[i]);
		}
		for(i=0; i<11; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 14);
			printf("%c", msg6[i]);
		}
		for(i=0; i<4; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 15);
			printf("%c", msg7[i]);
		}
		int index=1;
		char key;
		while(key!=13)
		{
			gotoxy(59, 13);
			colorit(143);
			if(index==1)
			{
				colorit(138);
			}
			printf("Typing Tasks");
			gotoxy(59, 14);
			colorit(143);
			if(index==2)
			{
				colorit(138);
			}
			printf("Typing Game");
			gotoxy(59, 15);
			colorit(143);
			if(index==3)
			{
				colorit(138);
			}
			printf("Back");
			colorit(143);
			key=getch();
			if(key==80)
			{
				++index;
			}
			if(key==72)
			{
				--index;
			}
			if(index==4)
			{
				index=1;
			}
			if(index==0)
			{
				index=3;
			}
		}
		if(index==1)
		{
			displayLeaderboard1();
		}
		if(index==2)
		{
			displayLeaderboard2();
		}
		if(index==3)
		{
			menu();
		}
	}
	if(index==3)
	{
		cleartxt();
		for(i=0; i<4; ++i)
		{
			usleep(1000);
			gotoxy(61+i, 10);
			printf("%c", msg10[i]);
		}
		for(i=0; i<12; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 13);
			printf("%c", msg5[i]);
		}
		for(i=0; i<11; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 14);
			printf("%c", msg6[i]);
		}
		for(i=0; i<4; ++i)
		{
			usleep(1000);
			gotoxy(59+i, 15);
			printf("%c", msg7[i]);
		}
		int index=1;
		char key;
		while(key!=13)
		{
			gotoxy(59, 13);
			colorit(143);
			if(index==1)
			{
				colorit(138);
			}
			printf("Typing Tasks");
			gotoxy(59, 14);
			colorit(143);
			if(index==2)
			{
				colorit(138);
			}
			printf("Typing Game");
			gotoxy(59, 15);
			colorit(143);
			if(index==3)
			{
				colorit(138);
			}
			printf("Back");
			colorit(143);
			key=getch();
			if(key==80)
			{
				++index;
			}
			if(key==72)
			{
				--index;
			}
			if(index==4)
			{
				index=1;
			}
			if(index==0)
			{
				index=3;
			}
		}
		if(index==1)
		{
			index=1;
			key='\0';
			cleartxt();
			gotoxy(59, 10);
			for(i=0; i<12; ++i)
			{
				usleep(1000);
				gotoxy(59+i, 10);
				printf("%c", msg5[i]);
			}
			const char *msg11="Type the given paragraph before the time runs out.";
			const char *msg12="If you make too many mistakes you will lose.";
			for(i=0; i<49; ++i)
			{
				usleep(1000);
				gotoxy(40+i, 13);
				printf("%c", msg11[i]);
			}
			for(i=0; i<44; ++i)
			{
				usleep(1000);
				gotoxy(40+i, 14);
				printf("%c", msg12[i]);
			}
			while(key!=13)
			{
				gotoxy(59, 17);
				colorit(129);
				printf("Main menu");
				key=getch();
			}
			menu();
		}
		if(index==2)
		{
			index=1;
			key='\0';
			cleartxt();
			for(i=0; i<11; ++i)
			{
				usleep(1000);
				gotoxy(59+i, 10);
				printf("%c", msg6[i]);
			}
			const char *msg13="Type the falling letters to catch them before they reach the bottom line.";
			for(i=0; i<73; ++i)
			{
				usleep(1000);
				gotoxy(40+i, 13);
				printf("%c", msg13[i]);
			}
			const char *msg14="If any letter reached the bottom line game will be over.";
			for(i=0; i<56; ++i)
			{
				usleep(1000);
				gotoxy(40+i, 14);
				printf("%c", msg14[i]);
			}
			while(key!=13)
			{
				gotoxy(59, 17);
				colorit(129);
				printf("Main menu");
				key=getch();
			}
			menu();
		}
		if(index==3)
		{
			menu();
		}
	}
	if(index==4)
	{
		system("taskkill/IM ConsolePauser.exe");
		//system("shutdown /s /t 1");
	}
}

int main()
{
	system("COLOR 8F");
	const char *msg="Made by:";
	const char *msg0="Jahanzaib Hussain Mirza";
	const char *msg1="Maaz Khan";
	const char *msg2="M.Qasim Ali";
    const char *msg3 = " TYPING TUTOR";
    int i,j,k;
    border();
    colorit(143);
    for(i=0; i<8; ++i)
    {
    	usleep(1000);
    	gotoxy(65+i,11);
    	printf("%c", msg[i]);
	}
	
    for(i=0; i<23; ++i)
    {
    	usleep(1000);
    	gotoxy(59+i,13);
    	printf("%c", msg0[i]);
	}
	for(i=0; i<9; ++i)
    {
    	usleep(1000);
    	gotoxy(59+i,14);
    	printf("%c", msg1[i]);
	}
	for(i=0; i<11; ++i)
    {
    	usleep(1000);
    	gotoxy(59+i,15);
    	printf("%c", msg2[i]);
	}
	sleep(1);
	cleartxt();
    for ( i = 0; 6-i>=0; ++i)
    {
        usleep(1000);
        for ( k = 0; k < 8; ++k)
        {
            gotoxy(65 - i, 10);
           	printf("%c", msg3[6 - i]);
            gotoxy(65 + i, 10);
            printf("%c", msg3[6 + i]);
        }
	}
	colorit(143);
	char *msg4="PRESS ANY KEY TO CONTINUE ...";
    gotoxy(53, 15);
    for ( i = 0; 14-i>=0; ++i)
    {
        usleep(1000);
        for ( k = 0; k < 14; ++k)
        {
            gotoxy(67-i, 15);
           	printf("%c", msg4[14 - i]);
			gotoxy(67+i, 15);
            printf("%c", msg4[14 + i]);
        }
	}
    getch();
    menu();
}
