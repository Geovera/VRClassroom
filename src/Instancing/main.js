const Koa           = require('koa');
const Router        = require("@koa/router");
const bodyParser    = require('koa-body');
const fetch         = require('node-fetch');

async function main(){

    const ue4Router = require('./ue4/router.js');

    const app = new Koa();
    const router = new Router();

    router.use('/ue4', ue4Router.routes(), ue4Router.allowedMethods());

    app.use(bodyParser());

    app.use(router.routes()).use(router.allowedMethods());

    const response = await fetch('http://localhost:1337/instances/add-world-server');
    // const data = await response.json();
    // console.log(data);

    app.listen(8181, () => console.log('Server Started'));

    
}

main();