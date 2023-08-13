import * as amqp from "amqplib";

async function connect() {
    try {
        const connection = await amqp.connect("amqp://localhost:5672");
        const channel = await connection.createChannel();
        await channel.assertQueue("jobs");

        console.log('Waiting for messages...');
        channel.consume("jobs", (msg) => {
            const input = JSON.parse(msg?.content.toString() ?? '');
            if (input.job_id) {
                console.log(`Recived job with id ${input.job_id}`);
                if (msg) {
                    channel.ack(msg);
                }
            }
        });
    } catch (err) {
        console.error(err);
    }
}

connect();
