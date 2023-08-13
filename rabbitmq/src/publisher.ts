import * as amqp from "amqplib";

const message = {
    job_id: 10
}

async function connect() {
    try {
        const connection = await amqp.connect("amqp://localhost:5672");
        const channel = await connection.createChannel();
        await channel.assertQueue("jobs");
        channel.sendToQueue("jobs", Buffer.from(JSON.stringify(message)));
        console.log(`Jobs sent successfully ${message.job_id}`);
    } catch (err) {
        console.error(err);
    }
}

connect();
