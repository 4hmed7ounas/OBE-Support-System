# OBE-Support-System

Many universities in the world are switching to Outcome Based Education these days. OBE is a way of designing and organizing curriculum. OBE also guides about testing and examination. Idea is to first define some learning outcomes, and then design programs and courses to meet these objectives.

Learning outcomes are first defined at program level (program learning outcomes), and then for each course further low-level outcomes are proposed (course learning outcomes). Each CLO should satisfy some PLO. A PLO may have multiple CLO's.

Evaluations (assignments, exams, etc) are also designed based on learning outcomes. Each question/problem needs to test a CLO. Normally it is required that each CLO should be tested by at least two different questions or problems.


You are required to develop a software system to support OBE in an institute of higher education. The system has two types of users: academic officers and teachers. An AO shall enter/manage information about programs, courses, PLO's and CLO's. A teacher shall enter the topics covered against each CLO. The teacher shall also add information about various evaluations (quizzes, assignments, exams, etc) conducted. Each evaluation shall test one or more CLO's. For every question of an evaluation, the teacher shall mention the particular CLO to be tested.


Develop the OBE system using C++. Provide interface to manage (add/remove/update) the following entities: courses, CLO's, evaluations and questions. Also the system shall be able to generate the following reports/queries:

1) Check whether a CLO has been tested or not (in two different questions)
2) Check whether all CLO's of a given course has been tested or not
3) For a given PLO, generate a list of all the relevant courses


Do not use any DBMS; instead save your data in files. Development of the business layer (classes) is a must!
