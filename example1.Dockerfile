FROM redis:6

RUN apt-get update -y && apt-get install -y build-essential
COPY . /tmp
RUN cd /tmp && make example1

CMD ["redis-server", "--loadmodule", "/tmp/module1.so"]
