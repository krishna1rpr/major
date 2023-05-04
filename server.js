const express = require('express');

const { spawn } = require('child_process');

const app = express();
const bodyParser = require('body-parser');
const port = 3000;

// configure the app to use bodyParser middleware to parse JSON data
app.use(bodyParser.json());

app.get('/', (req, res) =>{
    res.send("hello world")
})

// define a route to handle the POST request
app.post('/submit-form', (req, res) => {
    const formData = req.body;

    // create an array of arrays with the coordinates of the vertices of each box
    const boxes = formData.vertices.map((vertex, i) => {
        const boxCoords = [
            vertex,
            formData.vertices[i + 1],
            formData.vertices[i + 2],
            formData.vertices[i + 3]
        ];
        return boxCoords.filter(coords => coords !== undefined);
    }).filter(box => box.length === 4);

    console.log('Box Labels:', formData.boxLabels);
    console.log('Box Vertices:', boxes);

    res.send('Form submitted successfully');
});

app.get('/test', (req, res) => {

    exec("./B-tree/main", (error, stdout, stderr) => {

        console.log("STDOUT -------------");
        console.log(stdout);
        console.log("STDERR -------------");
        console.log(stderr);
        console.log("ERROR -------------");
        console.log(error);
        
        res.send(stdout);
    });
    
    // const bTree = spawn('./B-tree/main');

    // bTree.stdout.on('data', (data) => {
    //     res.send(data.toString());
    // });
    
    // bTree.stderr.on('data', (data) => {
    // console.error(`stderr: ${data}`);
    // });
    
    // bTree.on('close', (code) => {
    // console.log(`child process exited with code ${code}`);
    // });
})

// start the server
app.listen(port, () => {
    console.log(`Server started on port ${port}`);
});
