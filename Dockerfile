FROM debian:buster-slim 
WORKDIR /app
COPY . .
RUN apt-get update && apt-get install -y gcc && gcc main.c server.c -o main 

EXPOSE 8080
CMD [ "./main" ]
