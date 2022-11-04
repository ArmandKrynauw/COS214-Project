$(document).ready(function () {
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
        // updateUI(data);\
        displaySimulation(data);
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
  $(`body`).click(() => {
    request.command = "getAvailableSimulations";
    sendMessage(JSON.stringify(request));
  });

  // display the data from socket in the html
  displaySimulation = (simulation) => {
    console.log("heyy" + simulation);

    simulation.forEach((element, index) => {
      let battleName = element.name;
      let countries = element.countries;
      let countryImagasArray = [];
      let countryImagasArray1 = [];
      let countryImagasArray2 = [];

      // divide the countries into 2 arrays (for display purposes)
      countries.forEach((country) => {
        let countryCode = country.countryCode;
        let countryImg = countryCode + "flag.gif";
        countryImagasArray.push(countryImg);
      });

      const middleIndex = Math.ceil(countryImagasArray.length / 2);
      countryImagasArray1 = countryImagasArray.splice(0, middleIndex);
      countryImagasArray2 = countryImagasArray.splice(-middleIndex);

      console.log(countryImagasArray1);
      console.log(countryImagasArray2);

      // create the html for the battles and append to battlesList
      if (countryImagasArray1.length == 2) {
        $("<button></button>", {
          id: index,
          type: "button",
          class: "list-group-item list-group-item-action text-center",
          html: `<div class="warInfo">
                  <div class="warName">${battleName}</div>
                  <div class="mt-3 mb-3">
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray1[0]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray2[1]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                    
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray2[0]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray1[1]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                  </div>
                </div>`,
        }).appendTo(".list-group");
      } else {
        $("<button></button>", {
          id: index,
          type: "button",
          class: "list-group-item list-group-item-action text-center",
          html: `<div class="warInfo">
                  <div class="warName">${battleName}</div>
                  <div class="mt-3 mb-3">
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray1[0]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                    
                    <img
                    class="flagImage"
                    src="images/${countryImagasArray2[0]}"
                    alt=""
                    width="450px"
                    height="450px"
                    />
                  </div>
                </div>`,
        }).appendTo(".list-group");
      }
    });
  };

  // when a battle is clicked send the id of the battle via url to index.html
  $(document).on("click", ".list-group-item", function () {
    let battleName = $(this).attr("id");
    window.location.href = "../index.html?battleIndex=" + battleName;
  });
});
