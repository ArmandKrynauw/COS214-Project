var ws;
// let buttonCounter = 0;
let nextIndex = 0;

/**
 * If prewar is tue then the game is in prewar phase else it is in the postwar phase
 */
let preWar = true;

/**
 * Json format to send to warsocket
 * 
 * Remember to set command before each send
 * Only "selectSimulation" needs the "param" as of know
 * 
 * Example:
 * request.command = "selectSimulation";
 * request.param = 0;
 * ws.send(JSON.stringify(request));
 */
var request = {
  "command" : "",
  "param" : 0
}

function connectWarSocket() {
  if (ws) {
    ws.close();
    return;
  }
  ws = new WebSocket("ws://127.0.0.1:8000/websocket");
  if (!ws) return;

  ws.onopen = function () {
    console.log("Connection Opened");
  };
  ws.onmessage = function (ev) {
    data = JSON.parse(ev.data);
    if(data.hasOwnProperty("error")){
      console.log("Error: " + data.error);
    }
    else{
      updateUI(data);
    }
  };
  ws.onerror = function (ev) {
    console.log("Error: " + ev);
  };
  ws.onclose = function () {
    console.log("Connection Closed");
    ws = null;
  };
}

function sendMessage(message) {
  if (!ws) return;
  ws.send(message);
}

connectWarSocket();

$(`.nextRound`).click(() => {
  if (preWar) {
    //set command that is sent
    request.command = "loadNextRound";
    sendMessage(JSON.stringify(request));
    $(`.nextRound`).text("Start Round");
  } else {
    //set the command that is sent
    request.command = "loadRoundResults";
    sendMessage(JSON.stringify(request));
    $(`.nextRound`).text("Next  Round");
    nextIndex++;
  }
  preWar = !preWar;
});
updateUI = (data) => {
  /*-------nextBTN-------*/

  /**
   * Chnage the flags
   */
  $(`.img0`).attr(`src`, `./media/images/Germany.png`);
  $(`.img1`).attr(`src`, `./media/images/America.png`);

  /**
   * this function is to simulate the next day in the battle it get data from the war engine object
   */
  const maxIndex = data.engine.duration;
  if (nextIndex < maxIndex) {
    nextIndex;
    $(`#Day`).text(`Day: ${nextIndex}`);
  } else {
    $(`#State`).text(`Game Over you dubm nonce 😲`);
  }

  $(`#Day`).text(`Day: ${nextIndex}`);

  /**
   * this function is to add the name of the country to the map
   */
  $(`#BattleName`).text("war in planet earth");
  /**
   * this function is to set the state of the battle
   */
  $(`#State`).text(data.engine.stage);

  /**
   * This fucntion puts the representative theatres into the theatremap so that it can be disaplyed to the client
   * @logic loop throught the json data and loop through each theathre then we loop through each threatre threatres data and place the name and info about the theatre in the
   * block
   */
  const theatres = data.theatres.data;
  theatres.forEach((theatre) => {
    $(`.area_${theatre.coordinates} > .TheatreName`).text(theatre.name);
    const theatreData = theatre.data;
    if (theatreData[0]) {
      theatreData.forEach((theatreData) => {
        // console.log(theatreData);
        let str = `<div class="TheatreHead">${theatreData.name}</div>`;
        $(`.area_${theatre.coordinates} > .data`).append(str);
      });
    }
  });

  /*----------modal----------*/

  // Get the modal
  var modal = document.getElementById("myModal");

  // Get the <span> element that closes the modal
  var span = document.getElementsByClassName("close")[0];

  /**
   * this function opens the modal and displays the countries inside the current threatre nad the units that are inside of the threatre
   * @stage1 open the modal with the correct data
   * @stage2 loop through the theatres and find the correct theatre
   * @stage3 loop through the theatre units and find the correct theatre
   */
  showfight = (id) => {
    /**
     * @stage1 open the modal with the correct data
     */
    modal.style.display = "block";
    const theatre = data.theatres.data;
    let loadIndex = -1;
    $(`.modal-content`).empty();
    for (let i = 0; i < theatre.length; i++) {
      if (theatre[i].coordinates === id) {
        loadIndex = theatre[i].data;
        $(`.modal-content`).append(
          `<div class="theatreNameDisplay">${theatre[i].name}</div>`
        );
      }
    }

    /**
     * @stage2 loop through the theatres and find the correct theatre
     */
    loadIndex.forEach((theatreData) => {
      const str = `
      <div class="card niceCards" style="width: 18rem">
          <img
            class="card-img-top img1"
            src="./media/images/${theatreData.name}.png"
            alt="Card image cap"
          />
          <div class="card-body head">
            <h5 class="card-title NameTheatre">${theatreData.name}</h5>
          </div>
          <div class="card-body">
            <p class="SeaPower"><i class="fa-solid fa-ship"></i>  SeaPower: ${theatreData.seaPower}</p>
            <p class="AirPower"><i class="fa-solid fa-jet-fighter"></i>  AirPower: ${theatreData.airPower}</p>
            <p class="LandPower"><i class="fa-solid fa-person-rifle"></i>  LandPower: ${theatreData.landPower}</p>
            <p class="UnitsShow" onclick="showUnitsModal('${theatreData.name}')"> <i class="fa-solid fa-truck-plane"></i>  Units  <i class="fa-solid fa-chevron-down"></i></p>
            <ul class="list-group list-group-flush ${theatreData.name} hide "></ul>
            </div>
        </div>
      `;
      $(`.modal-content`).append(str);
    });
    /**
     * @stage3 this function adds the units to the modal
     */
    const theatreUnits = data.theatreUnits.data;
    theatreUnits.forEach((theatreUnit) => {
      console.log(theatreUnit.units[0].units);
      if (theatreUnit.units[0].coordinates == id) {
        const units = theatreUnit.units[0].units;
        units.forEach((unit) => {
          let type;
          if (unit.type === "land") {
            type = `<i class="fa-solid fa-person-rifle"></i>`;
          } else if (unit.type === "air") {
            type = `<i class="fa-solid fa-jet-fighter"></i>`;
          } else {
            type = `<i class="fa-solid fa-ship"></i>`;
          }
          $(`.${theatreUnit.name}`).append(
            `<li class="list-group-item">${type} ${unit.name} ${Math.round(
              (unit.currentHP / unit.initialHP) * 100
            )}%</li>`
          );
        });
      }
    });
  };

  /**
   * Opens the units for the specific theatre
   */
  showUnitsModal = (name) => {
    $(`.${name}`).toggleClass("hide");
  };

  /**
   * closes the theatre modal
   */
  $(document).on("keyup", function (e) {
    if (e.key == "Enter" || e.key == "Escape") {
      modal.style.display = "none";
    }
  });

  /**
   * closes the theatre modal
   */
  window.onclick = function (event) {
    if (event.target == modal) {
      modal.style.display = "none";
    }
  };

  /*--------Overall work---------*/
  const overallUnits = data.overallUnits.data;

  overallUnits.forEach((overallUnit, i = 0) => {
    $(`.Name${i}`).text(overallUnit.name);
    const units = overallUnit.units;
    units.forEach((unit) => {
      let type;
      if (unit.type === "land") {
        type = `<i class="fa-solid fa-person-rifle"></i>`;
      } else if (unit.type === "air") {
        type = `<i class="fa-solid fa-jet-fighter"></i>`;
      } else {
        type = `<i class="fa-solid fa-ship"></i>`;
      }
      $(`.list${i}`).append(
        `<li class="list-group-item">${type}  ${unit.name}  ${Math.round(
          (unit.currentHP / unit.initialHP) * 100
        )}%</li>`
      );
    });
  });

  /*--------Allies---------*/
  /**
   * this function adds the allies to the allies section
   */
  const allies = data.alliances.data;

  allies.forEach((ally, i = 0) => {
    const countries = ally.countries;
    countries.forEach((country) => {
      $(`.Allies${i}List`).append(
        `<li class="list-group-item"><i class="fa-solid fa-font-awesome"></i>  ${country}</li>`
      );
    });
  });
  /**
   * These next few functions are there to dispaly the information on the units and 2 countries that are fighting
   */
  showLeftTroops = () => {
    $(`.list0`).toggleClass("hide");
  };

  showLeftAllies = () => {
    $(`.Allies0List`).toggleClass("hide");
  };

  showRightTroops = () => {
    $(`.list1`).toggleClass("hide");
  };

  showRightAllies = () => {
    $(`.Allies1List`).toggleClass("hide");
  };

  /**
   * this function shows the map
   */
  $(`.MapBTN`).click(() => {
    $(`.fightingMap`).toggleClass("hide");
  });
};
/**
 * Temporary json file to display the data
 */
// const data = {
//   engine: {
//     stage: "Early Stage",
//     duration: 4,
//     day: 1,
//     numberOfCountries: 2,
//     numberOfAlliances: 2,
//   },
//   countries: {
//     data: [
//       {
//         name: "Germany",
//         resources: 50,
//         totalUnits: 10,
//       },
//       {
//         name: "America",
//         resources: 60,
//         totalUnits: 5,
//       },
//       {
//         name: "France",
//         resources: 40,
//         totalUnits: 15,
//       },
//       {
//         name: "Russia",
//         resources: 45,
//         totalUnits: 18,
//       },
//     ],
//   },
//   alliances: {
//     data: [
//       {
//         name: "Allies",
//         countries: ["America", "France"],
//       },
//       {
//         name: "Central European Powers",
//         countries: ["Germany", "Russia"],
//       },
//     ],
//   },
//   theatres: {
//     data: [
//       {
//         name: "Sicily",
//         coordinates: "0-0",
//         data: [
//           {
//             name: "Germany",
//             landPower: 100,
//             seaPower: 20,
//             airPower: 40,
//           },
//         ],
//       },
//       {
//         name: "Tunisia",
//         coordinates: "0-1",
//         data: [
//           {
//             name: "Germany",
//             landPower: 100,
//             seaPower: 20,
//             airPower: 40,
//           },
//           {
//             name: "America",
//             landPower: 120,
//             seaPower: 30,
//             airPower: 20,
//           },
//           {
//             name: "Russia",
//             landPower: 100,
//             seaPower: 20,
//             airPower: 40,
//           },
//           {
//             name: "France",
//             landPower: 120,
//             seaPower: 30,
//             airPower: 20,
//           },
//         ],
//       },
//       {
//         name: "Normandy",
//         coordinates: "0-2",
//         data: [],
//       },
//       {
//         name: "Netherlands",
//         coordinates: "1-0",
//         data: [],
//       },
//       {
//         name: "Belgium",
//         coordinates: "1-1",
//         data: [
//           {
//             name: "Germany",
//             landPower: 100,
//             seaPower: 20,
//             airPower: 40,
//           },
//           {
//             name: "America",
//             landPower: 120,
//             seaPower: 30,
//             airPower: 20,
//           },
//         ],
//       },
//       {
//         name: "Ruhr",
//         coordinates: "1-2",
//         data: [],
//       },
//       {
//         name: "Paris",
//         coordinates: "2-0",
//         data: [
//           {
//             name: "Germany",
//             landPower: 100,
//             seaPower: 20,
//             airPower: 40,
//           },
//         ],
//       },
//       {
//         name: "Alsace-Lorraine",
//         coordinates: "2-1",
//         data: [],
//       },
//       {
//         name: "Italy",
//         coordinates: "2-2",
//         data: [
//           {
//             name: "America",
//             landPower: 120,
//             seaPower: 30,
//             airPower: 20,
//           },
//         ],
//       },
//     ],
//   },
//   theatreUnits: {
//     data: [
//       {
//         name: "Germany",
//         units: [
//           {
//             theatre: "Sicily",
//             coordinates: "0-0",
//             units: [
//               {
//                 name: "Foot Soldier",
//                 type: "land",
//                 initialHP: 50,
//                 currentHP: 10,
//                 damage: 5,
//               },
//               {
//                 name: "Luftwaffe A400M",
//                 type: "air",
//                 initialHP: 100,
//                 currentHP: 50,
//                 damage: 20,
//               },
//             ],
//           },
//         ],
//       },
//       {
//         name: "America",
//         units: [
//           {
//             theatre: "Italy",
//             coordinates: "2-2",
//             units: [
//               {
//                 name: "Foot Soldier",
//                 type: "land",
//                 initialHP: 50,
//                 currentHP: 10,
//                 damage: 5,
//               },
//               {
//                 name: "C-17",
//                 type: "air",
//                 initialHP: 100,
//                 currentHP: 50,
//                 damage: 20,
//               },
//             ],
//           },
//         ],
//       },
//     ],
//   },
//   overallUnits: {
//     data: [
//       {
//         name: "Germany",
//         units: [
//           {
//             name: "Foot Soldier",
//             type: "land",
//             initialHP: 50,
//             currentHP: 10,
//             damage: 5,
//           },
//           {
//             name: "Luftwaffe A400M",
//             type: "air",
//             initialHP: 100,
//             currentHP: 50,
//             damage: 20,
//           },
//         ],
//       },
//       {
//         name: "America",
//         units: [
//           {
//             name: "Foot Soldier",
//             type: "land",
//             initialHP: 50,
//             currentHP: 10,
//             damage: 5,
//           },
//           {
//             name: "C-17",
//             type: "air",
//             initialHP: 100,
//             currentHP: 50,
//             damage: 20,
//           },
//         ],
//       },
//     ],
//   },
//   casualties: {
//     data: [
//       {
//         name: "Germany",
//         units: [
//           {
//             theatre: "Sicily",
//             coordinates: "0-0",
//             units: [
//               {
//                 name: "Foot Soldier",
//                 type: "land",
//                 initialHP: 50,
//                 currentHP: 0,
//                 damage: 5,
//               },
//             ],
//           },
//         ],
//       },
//     ],
//   },
// };
