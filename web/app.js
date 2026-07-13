let currentConfig = null;

function displayEndpoints()
{
    const endpointList = document.getElementById("endpointList");
    endpointList.replaceChildren();

    if (currentConfig === null || currentConfig.endpoints.length === 0)
    {
        endpointList.textContent = "Brak endpointów.";
        return;
    }

    currentConfig.endpoints.forEach((endpoint, index) =>
    {
        const item = document.createElement("div");
        const text = document.createElement("span");
        const deleteButton = document.createElement("button");

        text.textContent =
            endpoint.description +
            " | " +
            endpoint.url +
            " | interfejs: " +
            endpoint.interface +
            " | interwał: " +
            endpoint.interval_ms +
            " ms | " +
            (endpoint.enabled ? "włączony" : "wyłączony");

        deleteButton.textContent = "Usuń";
        deleteButton.style.marginLeft = "10px";

        deleteButton.addEventListener("click", () =>
        {
            removeEndpoint(index);
        });

        item.appendChild(text);
        item.appendChild(deleteButton);
        endpointList.appendChild(item);
    });
}

function removeEndpoint(index)
{
    currentConfig.endpoints.splice(index, 1);
    displayEndpoints();

    document.getElementById("statusMessage").textContent =
        "Endpoint usunięty. Kliknij „Zapisz konfigurację”, aby zapisać zmiany.";
}

async function loadConfig()
{
    const statusMessage = document.getElementById("statusMessage");

    try
    {
        const response = await fetch("/api/config");

        if (!response.ok)
            throw new Error("Nie udało się pobrać konfiguracji.");

        currentConfig = await response.json();
        displayEndpoints();

        statusMessage.textContent = "Konfiguracja wczytana.";
    }
    catch (error)
    {
        statusMessage.textContent = "Błąd: " + error.message;
    }
}

function addEndpoint()
{
    const description =
        document.getElementById("descriptionInput").value.trim();

    const ip =
        document.getElementById("ipInput").value.trim();

    const interfaceName =
        document.getElementById("interfaceInput").value.trim();

    const interval =
        Number(document.getElementById("intervalInput").value);

    const enabled =
        document.getElementById("enabledInput").checked;

    const statusMessage =
        document.getElementById("statusMessage");

    if (description === "" || ip === "" || interfaceName === "")
    {
        statusMessage.textContent =
            "Wypełnij opis, IP i interfejs.";

        return;
    }

    if (!Number.isInteger(interval) || interval <= 0)
    {
        statusMessage.textContent =
            "Interwał musi być dodatnią liczbą całkowitą.";

        return;
    }

    if (currentConfig === null)
        currentConfig = { endpoints: [] };

    const url =
        "http://" + ip + "/awp/api/api.html";

    currentConfig.endpoints.push(
    {
        description: description,
        enabled: enabled,
        interface: interfaceName,
        interval_ms: interval,
        url: url
    });

    displayEndpoints();

    statusMessage.textContent =
        "Endpoint dodany. Kliknij „Zapisz konfigurację”, aby zapisać zmiany.";

    document.getElementById("descriptionInput").value = "";
    document.getElementById("ipInput").value = "";
    document.getElementById("interfaceInput").value = "";
    document.getElementById("intervalInput").value = "1000";
    document.getElementById("enabledInput").checked = true;
}

async function saveConfig()
{
    const statusMessage =
        document.getElementById("statusMessage");

    if (currentConfig === null)
    {
        statusMessage.textContent =
            "Najpierw wczytaj konfigurację.";

        return;
    }

    statusMessage.textContent = "Zapisywanie...";

    try
    {
        const response = await fetch("/api/config",
        {
            method: "POST",
            headers:
            {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(currentConfig)
        });

        if (!response.ok)
            throw new Error("Nie udało się zapisać konfiguracji.");

        await response.json();

        statusMessage.textContent = "Konfiguracja zapisana.";
    }
    catch (error)
    {
        statusMessage.textContent = "Błąd: " + error.message;
    }
}

document
    .getElementById("loadButton")
    .addEventListener("click", loadConfig);

document
    .getElementById("saveButton")
    .addEventListener("click", saveConfig);

document
    .getElementById("addButton")
    .addEventListener("click", addEndpoint);

loadConfig();