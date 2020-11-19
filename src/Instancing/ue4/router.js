const Router    = require('@koa/router');
const CONFIG    = require('./config.js');
const {spawn}   = require('child_process');

const router = new Router();

router.post('/', (ctx, next) => {
    const body = ctx.request.body;

    
    const sub = spawn(CONFIG.UE4_PATH, [CONFIG.PROJECT_PATH, `${body.name}?listen`, '-server', '-log', '-nosteam', '-messaging', `-port=${body.port}`], {
        detached: true,
        stdio: 'ignore'
    });

    sub.unref();

    ctx.response.status = 204;
});

module.exports = router;