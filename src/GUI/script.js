const getJson = () =>
  $.getJSON("../utilities/simulations.json", function (data) {
    data = data["Wars"];
    console.log(data);
    //Set the Name of the War
    $("#BattleName").text(data[0].WarTitle);
    //Set the State of the War
    for (let m = 0; m < 2; m++) {
      // Set the Name of each country
      let countires = data[0].countries;
      $(`.Name${m}`).text(countires[m].name);
      //set the resources
      $(`.Res${m}`).html(
        `<i class="fa-solid fa-money-bill-1-wave"></i>  Resorces: ${countires[m].baseResourceCount}`
      );
      //Set the troops
      let troops = countires[m].units;
      troops.sort((a, b) => (Object.keys(a) > Object.keys(b) ? 1 : -1));
      for (let i = 0; i < troops.length; i++) {
        let typeI;
        if (
          Object.keys(troops[i]) == "HeavyAirUnit" ||
          Object.keys(troops[i]) == "LightAirUnit" ||
          Object.keys(troops[i]) == "MediumAirUnit"
        ) {
          typeI = `<i class="fa-solid fa-jet-fighter"></i>`;
        } else if (
          Object.keys(troops[i]) == "LightLandUnit" ||
          Object.keys(troops[i]) == "MediumLandUnit" ||
          Object.keys(troops[i]) == "HeavyLandUnit"
        ) {
          typeI = `<i class="fa-solid fa-truck-moving"></i>`;
        } else {
          typeI = `<i class="fa-solid fa-ship"></i>`;
        }
        $(`.list${m}`).append(
          `<li class="list-group-item">${typeI}  ${Object.values(
            troops[i]
          )}</li>`
        );
      }
      $(`.Units${m}`).html(
        `<i class="fa-solid fa-jet-fighter-up"></i>  Units: ${countires[0].units.length} <i class="fa-solid fa-chevron-down"></i>`
      );
      // Set the alliances
      let allies = data[0].alliances;
      let factions = m == 0 ? allies[m].Faction1 : allies[m].Faction2;
      $(`.Allies${m}`).html(
        `<i class="fa-solid fa-user-group"></i>  Allies: ${factions.length} <i class="fa-solid fa-chevron-down"></i>`
      );
      if (factions.length == 0) {
        $(`.Allies${m}List`).append(
          `<li class="list-group-item"><i class="fa-regular fa-flag"></i>  No Allies</li>`
        );
      }
      for (let i = 0; i < factions.length; i++) {
        $(`.Allies${m}List`).append(
          `<li class="list-group-item"><i class="fa-regular fa-flag"></i>  ${factions[i]}</li>`
        );
      }

      // Set the stratergy
      $(`.Start${m}`).html(`<i class="fa-regular fa-map"></i>  Strategy: OP`);
    }

    // console.log(factions);
  });

getJson();

// -------------------- dropDowns

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
