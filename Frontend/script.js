function addBox() {
    var form = document.getElementById("box-form");

    // create a new set of input fields for a box
    var boxLabel = document.createElement("input");
    boxLabel.type = "text";
    boxLabel.name = "box-label[]";
    boxLabel.placeholder = "Box Label";

    var vertex1 = document.createElement("input");
    vertex1.type = "text";
    vertex1.name = "vertex[]";
    vertex1.placeholder = "Top-Left X,Y";
    vertex1.required = true;

    var vertex2 = document.createElement("input");
    vertex2.type = "text";
    vertex2.name = "vertex[]";
    vertex2.placeholder = "Top-Right X,Y";
    vertex2.required = true;

    var vertex3 = document.createElement("input");
    vertex3.type = "text";
    vertex3.name = "vertex[]";
    vertex3.placeholder = "Bottom-Left X,Y";
    vertex3.required = true;

    var vertex4 = document.createElement("input");
    vertex4.type = "text";
    vertex4.name = "vertex[]";
    vertex4.placeholder = "Bottom-Right X,Y";
    vertex4.required = true;

    // add the new input fields to the form
    form.appendChild(boxLabel);
    form.appendChild(vertex1);
    form.appendChild(vertex2);
    form.appendChild(vertex3);
    form.appendChild(vertex4);
    form.appendChild(document.createElement("br"));
}

function submitForm() {
    var form = document.getElementById("box-form");

    // collect the form data as an object
    var formData = {
        boxLabels: [],
        vertices: []
    };

    var boxes = form.querySelectorAll("[name='box-label[]']");
    for (var i = 0; i < boxes.length; i++) {
        formData.boxLabels.push(boxes[i].value);
    }

    var vertices = form.querySelectorAll("[name='vertex[]']");
    for (var i = 0; i < vertices.length; i++) {
        var coords = vertices[i].value.split(",");
        formData.vertices.push({x: coords[0], y: coords[1]});
    }

    // send the form data as a POST request
    var xhr = new XMLHttpRequest();

    // define the POST request URL
    var url = "/submit-form";

    // set up the POST request
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json");

    // send the POST request
    xhr.send(JSON.stringify(formData));
}