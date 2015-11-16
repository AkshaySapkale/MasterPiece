
----------------------- TransEase 1.0  --------------------------


	Name: Akshay Ramchandra Sapkale
	MIS ID: 111408052


-------------------------------------------------------------------

Index :-

	1. What is TransEase ?
	2. Why do we need TransEase ?
	3. How does TrasnEase Work ?
	4. Difference between TransEase and other appliations (Unique Features)
	5. How TransEase is Secure than other applications.
	6. About FOSS.

---------------------------------------------------------------------

1. What is TransEase ?

	'TrasnEase' is open-source application ( Command-line utility) 
	that is build for Linux-platform.
	As its name, This application let you manage largers files easily by 
	splitting them into smaller parts and Re-merge them successfully without
	any data-loss/quality-loss.


2. Why do we need TransEase ?

	Many times, We have to send/transfer files that must have smaller size 
	than their original size (say, data-compression isn't useful in this case.)
	In such situaations, We need applications like TransEase that does job !
	eg. Email-attachments.
	How will you send a file with size 100 MB. as Email-attachment when you
	can only share files with size less than 30-40 MB ?
	Also You have restrictions that, You can't send files with particular-formats
	via E-mail ?
	No Worries .. ! TransEase is Always there !


3. How does TransEase work ?

	Basically, TransEase is Commandline utility.
	Applications takes certain arguments to fulfil its job.
	Byte-to-Byte data-copying is basic theme for this utility.
	Suppose, We have a file with name 'videosong.mp4' and size '100 MB'.
	And, We have to split this files into slices of 20 MB.
	So argument will be as:-

	arsapkale@Inspiron-3543:~$ ./project -s videosong.mp4 20m

	After this instruction, 5 files having size 20 MB will be created.
	such as videosong.mp4.001 , videosong.mp4.002 ...etc.

	For Merging them back, argument will be:- 

	arsapkale@Inspiron-3543:~$ ./project -j videosong.mp4.001

	Bla Bla Bla ... Your Re-merged files is Ready to Use Again !


4. Difference between TrasnEase & Other similar applications ?

	Other Applications:

	1. Algorithm deals with names of file,not exact data.
	2. If files are renamed,other applications will fail to remerge them.
	3. As dealing with names of files, If there are other fake,renamed files
	   then, other applications will merge them also without data-checking.
	4. They don't have Advanced-Data checking feature.
	5. If You renamed 10 different files with name pattern that other softwares follow,
	   it will simply merge them too :p !	


	TransEase :
	
	1. TrasnEase deals with names of files AS WELL AS EXACT-DATA CONTENTS.
	2. TransEase creates its own Data-Identity-Module (.dim file).
	3. . dim files are used to verify data-contents that are being merged.
	4. If fake,renamed files are encountered, TransEase will notify you and stop merging
	   asap.
      * 5. TransEase have one best feature - Advanced-Data Checking.
	   
	Advanced-Data Checking :-

	Suppose, you have to merge files to get your original one
	and you/somebody accidently renamed/deleted file then .. ?

	No Problem, Advanced-Data Checking will solve your problem.
	It will scan, analyse ALL FILES IN DIRECTORY according to
	Data-Identity-Module & Give you proper instructions.

	If files are deleted then, Nothing can happen :(
	But, If renamed, then TransEase will let you know which
	is your files and request you to rename this manually
	for further operation (v 1.0)

	About Manual Renaming : This is disadvantage, but still better than available ones !
				(TransEase 1.1 will do Automated-Renaming !)

	Data-Identity-Module :-
	
	This file will keep some information about each splitted-file.


5. How TransEase is Secure than other Applications ?

	It's simple .. Advanced-Data Checking algorithms !



6. About FOSS
	
	I believe, "Real Artists ship".
	I support Free Open-Source Software, I promote and I am Proud of !
	

--------------------------  Thank You ! ---------------------------		
	









