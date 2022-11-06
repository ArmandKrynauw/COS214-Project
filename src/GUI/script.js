var ws;
let nextIndex = 0;
let Nations = new Array();
let loadBattle = true;
let team4 = false;
let leftSide = false;
let rightSide = false;
let selectBattle = true;
var data;
let maxIndex = 8;

/**
 * If prewar is tue then the game is in prewar phase else it is in the postwar phase
 */
var preWar = true;

/**
 * Get the get paramaters from the url
 */
const urlParams = new URLSearchParams(window.location.search);
const battleIndex = urlParams.get("battleIndex");

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
  command: "",
  param: 0,
};

connectWarSocket = () => {
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
    if (data.hasOwnProperty("error")) {
      console.log("Error: " + data.error);
    } else {
      if (loadBattle) {
        initialiseBattle(data);
        loadBattle = false;
      } else if (selectBattle) {
        selectBattle = false;
      } else {
        data = data;
        updateUI(data);
      }
    }
  };
  ws.onerror = function (ev) {
    console.log("Error: " + ev);
  };
  ws.onclose = function () {
    console.log("Connection Closed");
    ws = null;
  };
};

sendMessage = (message) => {
  if (!ws) return;
  ws.send(message);
};

connectWarSocket();

timerLoad2 = () => {
  // second to execute
  request.command = "selectSimulation";
  request.param = parseInt(battleIndex);
  sendMessage(JSON.stringify(request));
  $(`.nextRound`).text("Load Battle   ");
};

timerLoad = () => {
  // fisrt to execute
  request.command = "getAvailableSimulations";
  sendMessage(JSON.stringify(request));
  window.setTimeout(timerLoad2, 500);
};

window.setTimeout(timerLoad, 500);

var click = 0;
$(`.nextRound`).click(() => {
  if (click < 10) {
    if (preWar) {
      request.command = "loadNextDay";
      $(`.nextRound`).text("Display Results");
      sendMessage(JSON.stringify(request));
    } else {
      request.command = "loadDayResults";
      sendMessage(JSON.stringify(request));
      $(`.nextRound`).text("Load Battle   ");
      nextIndex++;
    }
    preWar = !preWar;
  } else {
    $(`.nextRound`).hide();
    $(`#State`).text(`The battle is over`);
  }
  click++;
});
updateUI = (data) => {
  // console.log(data.theatres.data);
  /**
   * Clear the theatres
   */
  for (let m = 0; m < 3; m++) {
    for (let n = 0; n < 3; n++) {
      $(`.area_${m}-${n} .data`).empty();
    }
  }

  /**
   *This will set the resources of each country
   *1st param = countries index 2nd is the left or right side of screen 3rd is data
   */
  setResources(0, 0, data);
  setResources(1, 1, data);
  /**
   * this function is to simulate the next day in the battle it get data from the war engine object
   */
  // maxIndex = data.engine.duration;
  $(`#Day`).text(`Day: ${nextIndex + 1}`);

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
        if (
          theatreData.airPower == 0 &&
          theatreData.landPower == 0 &&
          theatreData.seaPower == 0
        ) {
        } else {
          // ✠
          let str = `<div class="TheatreHead">🦒 ${theatreData.name}</div>`;
          $(`.area_${theatre.coordinates} > .data`).append(str);
        }
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
      if (
        theatreData.airPower == 0 &&
        theatreData.landPower == 0 &&
        theatreData.seaPower == 0
      ) {
      } else {
        const str = `
        <div class="card niceCards" style="width: 18rem">
        <img
            class="card-img-top img1"
            src="./media/images/${theatreData.name.replace(" ", "")}.png"
            alt="Card image cap"
            />
            <div class="card-body head">
            <h5 class="card-title NameTheatre">${theatreData.name}</h5>
            </div>
            <div class="card-body">
            <p class="SeaPower"><i class="fa-solid fa-ship"></i>  SeaPower: ${
              theatreData.seaPower
            }</p>
            <p class="AirPower"><i class="fa-solid fa-jet-fighter"></i>  AirPower: ${
              theatreData.airPower
            }</p>
            <p class="LandPower"><i class="fa-solid fa-person-rifle"></i>  LandPower: ${
              theatreData.landPower
            }</p>
            <p class="Strat${theatreData.name.replace(
              " ",
              ""
            )}"><i class="fa-regular fa-map"></i> None </p>
              <p class="UnitsShow" onclick="showUnitsModal('${theatreData.name.replace(
                " ",
                ""
              )}')"> <i class="fa-solid fa-truck-plane"></i>  Units  <i class="fa-solid fa-chevron-down"></i></p>
                <ul class="list-group list-group-flush ${theatreData.name.replace(
                  " ",
                  ""
                )} hide "></ul>
                  </div>
                  </div>
                  `;
        $(`.modal-content`).append(str);
      }
    });
    /**
     * @stage3 this function adds the units to the modal
     */
    const theatreUnits = data.theatreUnits;
    theatreUnits.forEach((theatreUnit) => {
      const individualTheatres = theatreUnit.theatres;
      individualTheatres.forEach((individualTheatre) => {
        if (individualTheatre.coordinates == id) {
          const units = individualTheatre.units;
          units.forEach((unit) => {
            let type;
            if (unit.type === "land") {
              type = `<i class="fa-solid fa-person-rifle"></i>`;
            } else if (unit.type === "air") {
              type = `<i class="fa-solid fa-jet-fighter"></i>`;
            } else {
              type = `<i class="fa-solid fa-ship"></i>`;
            }
            let percentage = Math.round(
              (unit.currentHP / unit.initialHP) * 100
            );
            $(`.${theatreUnit.name.replace(" ", "")}`).append(
              // `<li class="list-group-item">${type} ${unit.name} ${Math.round(
              //   (unit.currentHP / unit.initialHP) * 100
              // )}%</li>`
              `<li class="list-group-item">
                <div>${type} ${unit.name}</div>
                <div class=" mb-2 list-group-item progress-bar progress-bar-danger progress-bar-striped active" 
                role="progressbar" aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:${percentage}%">    
              </div></li>`
            );
          });
        }
      });
    });
    /**
     * This will add the stratery to the card of the country
     */
    const strats = data.strategies.data;
    strats.forEach((strat) => {
      const NationData = strat.country;
      const NationTheatres = strat.theatres;
      NationTheatres.forEach((NationTheatre) => {
        const coords = NationTheatre.coordinates;
        if (coords == id) {
          // console.log(NationTheatre);
          $(`.Strat${NationData.replace(" ", "")}`).html(
            `<i class="fa-regular fa-map"></i> ${NationTheatre.strategy} <br> <i class="fa-solid fa-bullseye"></i>  ${NationTheatre.target}`
          );
        }
      });
    });

    HideModal = () => {
      modal.style.display = "none";
    };
  };

  /**
   * Opens the units for the specific theatre
   */
  showUnitsModal = (name) => {
    $(`.${name}`).toggleClass("hide");
  };

  /**
   *
   */
  showUnitsCasualties = (name) => {
    $(`.CasualtiesUL${name}`).toggleClass("hide");
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

  if (team4) {
    if (leftSide) {
      switchflag(0, 2);
      // CHANGE THISSSSSSSSSSSSSSSSSSS
      displayUnits(2, 0, data);
      setResources(2, 0, data);
      displayCasualties(data, 2, 0);
      setMobANDRes(2, 0, data);
    } else {
      switchflag(0, 0);
      displayUnits(0, 0, data);
      setResources(0, 0, data);
      displayCasualties(data, 0, 0);
      setMobANDRes(0, 0, data);
    }

    if (rightSide) {
      switchflag(1, 3);
      // CHANGE THISSSSSSSSSSSSSSSSSSS
      displayUnits(3, 1, data);
      setResources(3, 1, data);
      displayCasualties(data, 3, 1);
      setMobANDRes(3, 1, data);
    } else {
      switchflag(1, 1);
      displayUnits(1, 1, data);
      setResources(1, 1, data);
      displayCasualties(data, 1, 1);
      setMobANDRes(1, 1, data);
    }
  } else {
    switchflag(0, 0);
    displayUnits(0, 0, data);
    setResources(0, 0, data);
    displayCasualties(data, 0, 0);
    setMobANDRes(0, 0, data);

    switchflag(1, 1);
    displayUnits(1, 1, data);
    setResources(1, 1, data);
    displayCasualties(data, 1, 1);
    setMobANDRes(1, 1, data);
  }

  /*--------Allies---------*/
  /**
   * this function adds the allies to the allies section
   */
  if (team4) {
    const allies = data.alliances.data;
    $(`.Allies0List`).empty();
    $(`.Allies1List`).empty();
    allies[0].countries.forEach((country) => {
      $(`.Allies0List`).append(
        `<li class="list-group-item"><i class="fa-regular fa-flag"></i> ${country}</li>`
      );
    });

    allies[1].countries.forEach((country) => {
      $(`.Allies1List`).append(
        `<li class="list-group-item"><i class="fa-regular fa-flag"></i> ${country}</li>`
      );
    });
  }
};
/**
 * Here is all the click Events
 */
$(`.Casualties0`).click(() => {
  $(`.cau0List`).toggleClass(`hide`);
});

$(`.Casualties1`).click(() => {
  $(`.cau1List`).toggleClass(`hide`);
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

showLeftRes = () => {
  $(`.listRes0`).toggleClass("hide");
};

showRightRes = () => {
  $(`.listRes1`).toggleClass("hide");
};

/**
 * This click changes  the sides of the battle
 */

$(`.img0`).click(() => {
  if (team4) {
    if (!leftSide) {
      switchflag(0, 2);
      displayUnits(2, 0, data);
      setResources(2, 0, data);
      displayCasualties(data, 2, 0);
      setMobANDRes(2, 0, data);
    } else {
      switchflag(0, 0);
      displayUnits(0, 0, data);
      setResources(0, 0, data);
      displayCasualties(data, 0, 0);
      setMobANDRes(0, 0, data);
    }
    leftSide = !leftSide;
  }
});

$(`.img1`).click(() => {
  if (team4) {
    if (!rightSide) {
      switchflag(1, 3);
      displayUnits(3, 1, data);
      setResources(3, 1, data);
      displayCasualties(data, 3, 1);
      setMobANDRes(3, 1, data);
    } else {
      switchflag(1, 1);
      displayUnits(1, 1, data);
      setResources(1, 1, data);
      displayCasualties(data, 1, 1);
      setMobANDRes(1, 1, data);
    }
    rightSide = !rightSide;
  }
});

/**
 * This function will initialise the battle
 */
initialiseBattle = (data) => {
  data = data[battleIndex];
  const countries = data.countries;
  if (countries.length == 4) {
    Nations.push(countries[0].name);
    Nations.push(countries[1].name);
    Nations.push(countries[3].name);
    Nations.push(countries[2].name);
  } else {
    data.countries.forEach((country) => {
      Nations.push(country.name);
    });
  }
  $(`#BattleName`).text(data.name);

  if (Nations.length == 2) {
    team4 = false;
  } else {
    team4 = true;
  }

  // console.log(Nations);

  /**
   * set the image flags of each nation
   */
  $(`.img0`).attr("src", `./media/images/${Nations[0].replace(" ", "")}.png`);
  $(`.img1`).attr("src", `./media/images/${Nations[1].replace(" ", "")}.png`);
  $(`.Name0`).text(`${Nations[0]}`);
  $(`.Name1`).text(`${Nations[1]}`);
};

/**
 * Function to display all the UNITS currenlty fighting to the screen according to their index
 */
displayUnits = (index, side, overallUnits) => {
  overallUnits = data.overallUnits.data;
  $(`.list${side}`).empty();
  for (let i = 0; i < overallUnits.length; i++) {
    if (Nations[index] == overallUnits[i].name) {
      index = i;
      break;
    }
  }
  units = overallUnits[index].units;
  units.forEach((unit) => {
    let type;
    if (unit.type === "land") {
      type = `<i class="fa-solid fa-person-rifle"></i>`;
    } else if (unit.type === "air") {
      type = `<i class="fa-solid fa-jet-fighter"></i>`;
    } else {
      type = `<i class="fa-solid fa-ship"></i>`;
    }
    let percentage = Math.round((unit.currentHP / unit.initialHP) * 100);
    $(`.list${side}`).append(
      // `<li class="list-group-item">${type}  ${unit.name}  ${Math.round(
      //   (unit.currentHP / unit.initialHP) * 100
      // )}%</li>`
      `<li class="list-group-item">
        <div>${type}  ${unit.name}</div>
        <div class=" mb-2 list-group-item progress-bar progress-bar-danger progress-bar-striped active" 
        role="progressbar" aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:${percentage}%">
      </div></li>`
    );
  });
};

/**
 * this faunction will switch the flags of the nations and change their name
 */
switchflag = (side, country) => {
  $(`.img${side}`).attr(
    "src",
    `./media/images/${Nations[country].replace(" ", "")}.png`
  );
  $(`.Name${side}`).text(`${Nations[country]}`);
};

/**
 * This function loads in the casualties after each round
 * it takes all the countires current theatres and puts them into one
 * group
 */
displayCasualties = (data, country, side) => {
  // console.log(data.casualties);
  const casualties = data.casualties.data;
  $(`.cau${side}List`).empty();
  country = Nations[country].replace(" ", "");
  casualties.forEach((casualty) => {
    if (casualty.name.replace(" ", "") == country) {
      const theatres = casualty.theatres;
      theatres.forEach((theatre) => {
        const units = theatre.units;
        units.forEach((unit) => {
          let type;
          if (unit.type === "land") {
            type = `<i class="fa-solid fa-person-rifle"></i>`;
          } else if (unit.type === "air") {
            type = `<i class="fa-solid fa-jet-fighter"></i>`;
          } else {
            type = `<i class="fa-solid fa-ship"></i>`;
          }
          $(`.cau${side}List`).append(
            `<li class="list-group-item">${type}  ${unit.name} <br>
            <i class="fa-solid fa-location-pin"></i>    ${theatre.name}</li>`
          );
        });
      });
    }
  });
};

/**
 * this function will show the current nations resources
 */
setResources = (index, side, data) => {
  const resources = data.countries.data[index].resources;
  $(`.Res${side}`).empty();
  $(`.Res${side}`).html(
    `<i class="fa-solid fa-money-bill-wave"></i> Resources: ${resources}`
  );
};

/**
 * set the countrys current strategy
 */
setStrategy = (index, side, data) => {
  const strategy = data.countries.data[index].strategy;
  $(`.Str${side}`).empty();
  $(`.Str${side}`).html(
    `<i class="fa-solid fa-swords"></i> Strategy: ${strategy}`
  );
};

$(`#BattleName`).click(() => {
  window.location.href = "./splashPage/splash.html";
});

/**
 * Set Mobilization AND Research loops through the countries and check if the index is matching the current country
 */
setMobANDRes = (index, side, data) => {
  const research = data.research.data;
  research.forEach((indvRes) => {
    let percentageIndustry = Math.round((indvRes.industryCurrent / 500) * 100);
    let percentagePropaganda = Math.round(
      (indvRes.propagandaCurrent / 500) * 100
    );
    if (indvRes.name.replace(" ", "") == Nations[index].replace(" ", "")) {
      $(`.listRes${side}`).empty();
      $(`.listRes${side}`).append(
        // `<li class="list-group-item"><i class="fa-solid fa-coins"></i> Industry: ${percentageIndustry}</li>`
        `<li class="list-group-item">
          <i class="fa-solid fa-coins"></i> Industry 
          <br> 
          <div class=" mb-2 list-group-item progress-bar progress-bar-danger progress-bar-striped active" 
            role="progressbar" aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:${percentageIndustry}%">
          </div></li>`
      );
      $(`.listRes${side}`).append(
        // `<li class="list-group-item"><i class="fa-solid fa-volume-high"></i> Propeganda: ${percentagePropaganda}</li>`
        `<li class="list-group-item">
          <i class="fa-solid fa-volume-high"></i> Propaganda 
          <br> 
          <div class=" mb-2 list-group-item progress-bar progress-bar-danger progress-bar-striped active" 
            role="progressbar" aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:${percentagePropaganda}%">
          </div></li>`
      );
    }
  });
  const mobilization = data.mobilization.data;
  // console.log(mobilization);
  mobilization.forEach((indvMob) => {
    if (indvMob.name.replace(" ", "") == Nations[index].replace(" ", "")) {
      $(`.Mob${side}`).empty();
      $(`.Mob${side}`).html(
        `<i class="fa-solid fa-person-walking"></i> Mobilization: ${indvMob.mobilization}`
      );
    }
  });
};
