<h1 align="center"> COS 214 Project - War Simulator </h1>

![image](https://drive.google.com/uc?id=1txR5ga_jksTh8s4Q_TpBRcZVCXeaTRQO)

# Contents

- [Description](#description)
- [Documentation](#documentation)
- [Demo](#demo)
- [Setup](#setup)
- [Tests](#tests)
- [Team](#team)

# Description

Generic War Simulator providing a well-defined interface for simulations to be written, loaded, and run. A dynamic amount of different simulations can be run with varying specifications. These can be run to completion or through a design mode which allows the user to make tweaks as they step through the simulation. 

# Documentation

[Report](https://docs.google.com/document/d/1SO2EWCa2MpqC4dWhszZaXsbHXWcP98rih0-Rxo4v2IA/)

[API Documentation](https://demo.hedgedoc.org/enrh8j-uSU6jJ3V8m6NHWw?view)

[Doxygen Documentation](https://drive.google.com/file/d/1q-uM2htVxp-8KeQncFkuyCWmhxxETV5i/view?usp=sharing)

[Class Diagram](https://drive.google.com/uc?id=16rv7moVTcIt_6ylzExouiVvLD-Clw-pR)

# Demo

[Video Demo](https://drive.google.com/uc?id=1HHqHpLHMNCIoQHRqPR1zv6Di4xcEjwVe)

# Setup
### Prerequisites

* CMake >= 3.2

### Cloning
```
git clone https://github.com/ArmandKrynauw/COS214-Project
```
### Building
This project can be built using CMake:
```
mkdir build
cd build
cmake ..
make
```

### Running
For Web UI mode:
1. Start the WarSocket
```
make run
```
2. Launch the web interface
* Go to src/GUI/splashPage/
* Open splash.html

For design mode:
```
make dev
```

# Tests
### Prerequisites
* CMake >= 3.2
* libgtest

### Building
```
cd Test
mkdir build
cd build
cmake ..
make
```

### Running
```
./runTests
```

# Team 

<table>
    <tr><th>Member</th><th>Roles</th><th>Description</th></tr>
    <tr>
      <td align="center">
	  	Armand Krynauw <br> u04868286 <br>
		<img src="https://drive.google.com/uc?id=10EWX9n-1mTHSHxJwbsVRJLh1zBj6u7sp">
	  </td>
	  <td align="center">
	  	Team Lead <br> Backend <br> Documentation <br> Being sus<br><br>
		<a href="https://github.com/ArmandKrynauw">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
	  	A 2nd year BSc Computer Science student at the University of Pretoria interested in the magical world of Mathematics, Statistics and Software Engineering ???.
	  </td>
	</tr>
    <tr>
      <td align="center">
	  	Jake Mileham <br> u21692492 <br>
		<img src="https://drive.google.com/uc?id=17ee1L1ThuAZWEaC8YheOAk2PrI3T8dg4">
	  </td>
	  <td align="center">
	  	Backend <br> The Goat <br> Tik Tok Enjoyer <br> A Plant UML<br><br>
		<a href="https://github.com/SharkmanZA">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
	  	A 2nd year BsC Information and Knowledge Systems student at the University of Pretoria with a passion for Computational Intelligence and Geographic Information Systems. A developer who wants gratitude.
	  </td>
	</tr>
    <tr>
      <td align="center">
	  	Francois Combrinck <br> u21729752 <br>
		<img src="https://drive.google.com/uc?id=15OLe9jc7WAyrgjDbdJALzFucQA9dYx2Z">
	  </td>
	  <td align="center">
	  	Backend <br> Research <br> Documentation <br> Diagrams <br><br>
		<a href="https://github.com/CenturionLC">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
		 A computer science student who is passionate about learning new things and solving difficult problems. He is constantly striving to improve his skills and knowledge so that he can be the best computer science student he can be. He likes trains.
	  </td>
	</tr>
    <tr>
      <td align="center">
	  	Karel Olwage <br> u21555258 <br>
		<img src="https://drive.google.com/uc?id=1_zs5LACK3IMqbx_M2YwnO5VOxfZnkrSA">
	  </td>
	  <td align="center">
	  	Backend <br> Tester <br> No Sleep <br><br>
		<a href="https://github.com/Klairgo">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
	  	A computer science student at the University of Pretoria. Interested in computer secutiry and mathematics. I enjoy solving problems and not sleeping.
	  </td>
	</tr>
    <tr>
      <td align="center">
	  	Carl de Witt <br> u21444928
		<img src="https://drive.google.com/uc?id=1eD81d04quhUwDW4XN1HWiiFwfYBZg24H">
	  </td>
	  <td align="center">
	  	Frontend <br> Diagrams<br> Retired F1 Driver<br><br>
		<a href="https://github.com/CarlDeWitt">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
	  	I am a 2nd-year BIS Multimedia student at the University of Pretoria. I love full-stack development. My favourite language is PHP :0. I also love riding a bike.
	  </td>
	</tr>
    <tr>
      <td align="center">
	  	Carlie Van Wyk <br> u21672823
		<img src="https://drive.google.com/uc?id=11mzcBdUJcONE9QpbmVV0vKUfGxzKbjYH">
	  </td>
	  <td align="center">
	  	Frontend <br> Diagrams <br> PHP Expert <br><br>
		<a href="https://github.com/CarlieVanWyk">
			<img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white">
		</a>
	  </td>
	  <td>
	  	I am a 2nd year student and am currently loving the BIS Multimedia degree at TUKS. I love working with people and seeing hard work pay off.
	  </td>
	</tr>
</table>
