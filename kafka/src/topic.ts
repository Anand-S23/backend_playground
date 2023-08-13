import { Kafka } from "kafkajs";

async function run() {
    try {
        const kafka = new Kafka({
            clientId: 'my_app',
            brokers: ['localhost:9092']
        });

        const admin = kafka.admin();
        console.log('Admin connecting...');
        await admin.connect();
        console.log('Admin connected');
        await admin.createTopics({
            "topics": [{
                "topic": "Users",
                "numPartitions": 2 // Names A-N and M-Z
            }]
        });
        await admin.disconnect();
    } catch(err) {
        console.error(err);
    } finally {
        process.exit(0);
    }
}

run();
